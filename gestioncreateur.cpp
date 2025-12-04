#include "gestioncreateur.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
#include <QRandomGenerator>
#include <QPrinter>
#include <QTextDocument>
#include <QMessageBox>

GestionCreateur::GestionCreateur(Ui::MainWindow *ui_, QObject *parent)
    : QObject(parent), ui(ui_)
{
    ui->tab9->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab9->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab9->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    connect(ui->toolbuttajouter_2, &QToolButton::clicked, this, &GestionCreateur::ajouter);
    connect(ui->toolbutsupp_2, &QToolButton::clicked, this, &GestionCreateur::supprimer);
    connect(ui->toolbuttmodifier_2, &QToolButton::clicked, this, &GestionCreateur::modifier);
    connect(ui->toolbuttrecherche_2, &QToolButton::clicked, this, &GestionCreateur::rechercher);
    connect(ui->toolbutttrier_2, &QToolButton::clicked, this, &GestionCreateur::trier);
    connect(ui->toolButtonexporter, &QToolButton::clicked, this, &GestionCreateur::exporterPdf);
    connect(ui->toolButtonPredire, &QToolButton::clicked, this, &GestionCreateur::predire);
    connect(ui->toolButtonStats_2, &QToolButton::clicked, this, &GestionCreateur::statistiques);


    // Ne pas appeler predireDepuisTable au clic ! → éviter popup automatique
    // connect(ui->tab9, &QTableWidget::cellClicked, this, &GestionCreateur::predireDepuisTable);

    connect(ui->tab9, &QTableWidget::cellChanged, this, &GestionCreateur::onCellChanged);

    afficher();
}

GestionCreateur::~GestionCreateur() {}


// ============================================================
// AJOUTER
// ============================================================
void GestionCreateur::ajouter()
{
    QString id = ui->lineid_2->text().trimmed();
    QString nom = ui->linenom_2->text().trimmed();
    QString prenom = ui->lineprenom_2->text().trimmed();
    QString pseudo = ui->linepseudo_2->text().trimmed();
    QString telephone = ui->linetelephone_2->text().trimmed();
    QString plat = ui->comboBoxplat->currentText().trimmed();
    QString email = ui->lineemail_2->text().trimmed();

    if (id.isEmpty() || nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(nullptr, "Champs obligatoires",
                             "Veuillez remplir ID, nom et prénom.");
        return;
    }

    // Génération automatique d'abonnés
    int abonnes = 0;
    QString lowPlat = plat.toLower();

    if (lowPlat == "tiktok")
        abonnes = QRandomGenerator::global()->bounded(1000, 200000);
    else if (lowPlat == "instagram")
        abonnes = QRandomGenerator::global()->bounded(500, 150000);
    else if (lowPlat == "youtube")
        abonnes = QRandomGenerator::global()->bounded(100, 100000);
    else if (lowPlat == "facebook")
        abonnes = QRandomGenerator::global()->bounded(100, 50000);
    else
        abonnes = QRandomGenerator::global()->bounded(50, 20000);

    QSqlQuery query;
    query.prepare("INSERT INTO CREATEUR "
                  "(ID_CREATEUR, NOM, PRENOM, EMAIL, PSEUDO, TELEPHONE, RESEAU, ABONNES) "
                  "VALUES (:id, :nom, :prenom, :email, :pseudo, :tel, :reseau, :ab)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":pseudo", pseudo);
    query.bindValue(":tel", telephone);
    query.bindValue(":reseau", plat);
    query.bindValue(":ab", abonnes);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (ajout)", query.lastError().text());
        return;
    }

    QMessageBox::information(nullptr, "Succès", "Créateur ajouté.");
    afficher();
}


// ============================================================
// SUPPRIMER
// ============================================================
void GestionCreateur::supprimer()
{
    int row = ui->tab9->currentRow();

    if (row < 0) {
        QMessageBox::warning(nullptr, "Suppression", "Veuillez sélectionner une ligne à supprimer.");
        return;
    }

    QString id = ui->tab9->item(row, 0)->text();

    if (QMessageBox::question(nullptr, "Confirmation",
                              "Supprimer ce créateur (ID : " + id + ") ?")
        != QMessageBox::Yes)
    {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM CREATEUR WHERE ID_CREATEUR = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (suppression)", query.lastError().text());
        return;
    }

    ui->tab9->removeRow(row);
    QMessageBox::information(nullptr, "Succès", "Créateur supprimé !");
}


// ============================================================
// MODIFIER
// ============================================================
void GestionCreateur::modifier()
{
    QMessageBox::information(nullptr, "Modification",
                             "Modifiez directement dans le tableau.");
}


// ============================================================
// RECHERCHER
// ============================================================
void GestionCreateur::rechercher()
{
    QString crit = ui->linerech_2->text().trimmed();
    QSqlQuery q;

    bool isNumber = false;
    int idValue = crit.toInt(&isNumber);

    if (isNumber) {
        q.prepare("SELECT * FROM CREATEUR WHERE ID_CREATEUR = :id");
        q.bindValue(":id", idValue);
    }
    else {
        q.prepare("SELECT * FROM CREATEUR WHERE "
                  "LOWER(NOM) LIKE LOWER(:c) OR "
                  "LOWER(PRENOM) LIKE LOWER(:c) OR "
                  "LOWER(PSEUDO) LIKE LOWER(:c) OR "
                  "LOWER(TELEPHONE) LIKE LOWER(:c) OR "
                  "LOWER(RESEAU) LIKE LOWER(:c)");
        q.bindValue(":c", "%" + crit + "%");
    }

    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (recherche)", q.lastError().text());
        return;
    }

    remplirTableAvecQuery(q);
}


// ============================================================
// TRIER
// ============================================================
void GestionCreateur::trier()
{
    QString choix = ui->linetrie->currentText();
    QString colonne;

    if (choix == "Id")
        colonne = "ID_CREATEUR";
    else if (choix == "Nom")
        colonne = "NOM";
    else if (choix == "Prenom")
        colonne = "PRENOM";
    else
        colonne = "ID_CREATEUR";

    QSqlQuery query;

    QString sql = "SELECT * FROM CREATEUR ORDER BY " + colonne;

    if (!query.exec(sql)) {
        QMessageBox::warning(nullptr, "Erreur tri",
                             "Tri impossible : " + query.lastError().text());
        return;
    }

    remplirTableAvecQuery(query);
}


// ============================================================
// REMPLIR TABLE
// ============================================================
void GestionCreateur::remplirTableAvecQuery(QSqlQuery &q)
{
    ui->tab9->blockSignals(true);
    ui->tab9->setRowCount(0);

    int row = 0;
    while (q.next()) {
        ui->tab9->insertRow(row);
        for (int c = 0; c < 8; c++) // 8 colonnes maintenant
            ui->tab9->setItem(row, c, new QTableWidgetItem(q.value(c).toString()));
        row++;
    }

    ui->tab9->blockSignals(false);
}


// ============================================================
// EDIT CELL
// ============================================================
void GestionCreateur::onCellChanged(int row, int column)
{
    if (column == 0) {
        QMessageBox::warning(nullptr, "Erreur", "ID non modifiable.");
        afficher();
        return;
    }

    QString id = ui->tab9->item(row, 0)->text();
    QString nom = ui->tab9->item(row, 1)->text();
    QString prenom = ui->tab9->item(row, 2)->text();
    QString email = ui->tab9->item(row, 3)->text();
    QString pseudo = ui->tab9->item(row, 4)->text();
    QString telephone = ui->tab9->item(row, 5)->text();
    QString reseau = ui->tab9->item(row, 6)->text();
    QString abonnes = ui->tab9->item(row, 7)->text();

    QSqlQuery q;
    q.prepare("UPDATE CREATEUR SET NOM=:n, PRENOM=:p, EMAIL=:email, "
              "PSEUDO=:ps, TELEPHONE=:t, RESEAU=:r, ABONNES=:ab "
              "WHERE ID_CREATEUR=:id");

    q.bindValue(":n", nom);
    q.bindValue(":p", prenom);
    q.bindValue(":email", email);
    q.bindValue(":ps", pseudo);
    q.bindValue(":t", telephone);
    q.bindValue(":r", reseau);
    q.bindValue(":ab", abonnes);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", q.lastError().text());
        afficher();
    }
}


// ============================================================
// EXPORT PDF
// ============================================================
QString GestionCreateur::tableToHtml()
{
    QString html = "<h2>Liste des Créateurs</h2><table border=1 cellspacing=0 cellpadding=4>";
    html += "<tr>";
    for (int c = 0; c < ui->tab9->columnCount(); c++)
        html += "<th>" + ui->tab9->horizontalHeaderItem(c)->text() + "</th>";
    html += "</tr>";

    for (int r = 0; r < ui->tab9->rowCount(); r++) {
        html += "<tr>";
        for (int c = 0; c < ui->tab9->columnCount(); c++)
            html += "<td>" + ui->tab9->item(r, c)->text() + "</td>";
        html += "</tr>";
    }
    html += "</table>";

    return html;
}

void GestionCreateur::exporterPdf()
{
    QString file = QFileDialog::getSaveFileName(nullptr, "Exporter PDF", "", "*.pdf");
    if (file.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);

    QTextDocument doc;
    doc.setHtml(tableToHtml());
    doc.print(&printer);

    QMessageBox::information(nullptr, "PDF", "PDF exporté avec succès.");
}


// ============================================================
// AFFICHER
// ============================================================
void GestionCreateur::afficher()
{
    QSqlQuery q("SELECT * FROM CREATEUR");
    remplirTableAvecQuery(q);
}


// ============================================================
// PREDIRE avec bouton
// ============================================================
void GestionCreateur::predire()
{
    int row = ui->tab9->currentRow();

    if (row < 0) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Veuillez sélectionner un créateur dans le tableau !");
        return;
    }

    QString platform = ui->tab9->item(row, 6)->text().trimmed(); // colonne RESEAU

    if (platform.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Ce créateur n'a pas de plateforme.");
        return;
    }

    QString pythonExe = "C:/Users/moham/AppData/Local/Python/pythoncore-3.14-64/python.exe";
    QString script = "C:/Users/moham/projetiwen/predict.py";

    QProcess proc;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(pythonExe, QStringList() << script << platform);

    if (!proc.waitForFinished(8000)) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Le script Python n’a pas répondu (timeout).");
        return;
    }

    QString output = QString::fromLocal8Bit(proc.readAll()).trimmed();

    if (output.startsWith("ERROR:")) {
        QMessageBox::critical(nullptr, "Erreur Python", output);
        return;
    }

    QMessageBox::information(nullptr, "Prédiction",
                             "Meilleur moment pour publier sur " + platform + " : " + output + "h");
}
// ============================================================
// STATISTIQUES
// ============================================================
void GestionCreateur::statistiques()
{
    // 1) Lire les données depuis la BD
    QSqlQuery q("SELECT RESEAU, SUM(ABONNES) FROM CREATEUR GROUP BY RESEAU");

    QStringList categories;   // X axis
    QBarSet *barset = new QBarSet("Abonnés"); // Y values

    while (q.next())
    {
        QString reseau = q.value(0).toString();
        int abonnes = q.value(1).toInt();

        if (reseau.isEmpty())
            reseau = "(vide)";

        categories << reseau;
        *barset << abonnes;
    }

    // 2) Série
    QBarSeries *series = new QBarSeries();
    series->append(barset);

    // 3) Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre d'abonnés par plateforme");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 4) Axe X (catégories)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 5) Axe Y (valeurs)
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Abonnés");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 6) Affichage dans le widget UI
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    // Nettoyer ancien contenu
    QLayout *layout = ui->chartWidget->layout();
    if (!layout)
    {
        layout = new QVBoxLayout(ui->chartWidget);
        ui->chartWidget->setLayout(layout);
    }

    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    layout->addWidget(view);
}
