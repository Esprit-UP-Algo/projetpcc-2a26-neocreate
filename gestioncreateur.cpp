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
    ui->tab9_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab9_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab9_2->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    connect(ui->toolbuttajouter_3, &QToolButton::clicked, this, &GestionCreateur::ajouter);
    connect(ui->toolbutsupp_3, &QToolButton::clicked, this, &GestionCreateur::supprimer);
    connect(ui->toolbuttmodifier_3, &QToolButton::clicked, this, &GestionCreateur::modifier);
    connect(ui->toolbuttrecherche_3, &QToolButton::clicked, this, &GestionCreateur::rechercher);
    connect(ui->toolbutttrier_3, &QToolButton::clicked, this, &GestionCreateur::trier);
    connect(ui->toolButtonexporter_2, &QToolButton::clicked, this, &GestionCreateur::exporterPdf);
    connect(ui->toolButtonPredire_2, &QToolButton::clicked, this, &GestionCreateur::predire);
    connect(ui->toolButtonStats_2, &QToolButton::clicked, this, &GestionCreateur::statistiques);
    connect(ui->toolButtonDominante_2, &QToolButton::clicked, this, &GestionCreateur::plateformeDominante);

    connect(ui->tab9_2, &QTableWidget::cellChanged, this, &GestionCreateur::onCellChanged);

    afficher();
}

GestionCreateur::~GestionCreateur() {}

void GestionCreateur::ajouter()
{
    QString id = ui->lineid_3->text().trimmed();
    QString nom = ui->linenom_3->text().trimmed();
    QString prenom = ui->lineprenom_3->text().trimmed();
    QString pseudo = ui->linepseudo_3->text().trimmed();
    QString telephone = ui->linetelephone_3->text().trimmed();
    QString plat = ui->comboBoxplat_2->currentText().trimmed();
    QString email = ui->lineemail_3->text().trimmed();

    if (id.isEmpty() || nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(nullptr, "Champs obligatoires",
                             "Veuillez remplir ID, nom et prénom.");
        return;
    }

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

    QString pythonExe = "C:/Users/moham/AppData/Local/Python/pythoncore-3.14-64/python.exe";
    QString scriptMail = "C:/Users/moham/projetiwen/send_mail.py";

    QProcess mailProcess;
    mailProcess.setProcessChannelMode(QProcess::MergedChannels);
    mailProcess.start(
        pythonExe,
        QStringList() << scriptMail << nom << prenom << plat
        );

    mailProcess.waitForFinished();

    QString mailOutput = QString::fromLocal8Bit(mailProcess.readAll()).trimmed();

    if (mailOutput.contains("OK"))
        QMessageBox::information(nullptr, "Email", "Notification envoyée !");
    else
        QMessageBox::warning(nullptr, "Email", "Échec d'envoi : " + mailOutput);
}

void GestionCreateur::supprimer()
{
    int row = ui->tab9_2->currentRow();

    if (row < 0) {
        QMessageBox::warning(nullptr, "Suppression", "Veuillez sélectionner une ligne à supprimer.");
        return;
    }

    QString id = ui->tab9_2->item(row, 0)->text();

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

    ui->tab9_2->removeRow(row);
    QMessageBox::information(nullptr, "Succès", "Créateur supprimé !");
}

void GestionCreateur::modifier()
{
    QMessageBox::information(nullptr, "Modification",
                             "Modifiez directement dans le tableau.");
}

void GestionCreateur::rechercher()
{
    QString crit = ui->linerech_3->text().trimmed();
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

void GestionCreateur::trier()
{
    QString choix = ui->linetrie_2->currentText();
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

void GestionCreateur::remplirTableAvecQuery(QSqlQuery &q)
{
    ui->tab9_2->blockSignals(true);
    ui->tab9_2->setRowCount(0);

    int row = 0;
    while (q.next()) {
        ui->tab9_2->insertRow(row);
        for (int c = 0; c < 8; c++)
            ui->tab9_2->setItem(row, c, new QTableWidgetItem(q.value(c).toString()));
        row++;
    }

    ui->tab9_2->blockSignals(false);
}

void GestionCreateur::onCellChanged(int row, int column)
{
    if (ui->tab9_2->signalsBlocked())
        return;

    if (column == 0) {
        QMessageBox::warning(nullptr, "Erreur", "ID non modifiable.");
        afficher();
        return;
    }

    if (row < 0 || row >= ui->tab9_2->rowCount())
        return;

    auto safeGet = [&](int col) -> QString {
        QTableWidgetItem *item = ui->tab9_2->item(row, col);
        return item ? item->text().trimmed() : "";
    };

    QString id       = safeGet(0);
    QString nom      = safeGet(1);
    QString prenom   = safeGet(2);
    QString email    = safeGet(3);
    QString pseudo   = safeGet(4);
    QString telephone= safeGet(5);
    QString reseau   = safeGet(6);
    QString abonnes  = safeGet(7);

    if (id.isEmpty())
        return;

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
        ui->tab9_2->blockSignals(true);
        afficher();
        ui->tab9_2->blockSignals(false);
    }
}

QString GestionCreateur::tableToHtml()
{
    QString html = "<h2>Liste des Créateurs</h2><table border=1 cellspacing=0 cellpadding=4>";
    html += "<tr>";
    for (int c = 0; c < ui->tab9_2->columnCount(); c++)
        html += "<th>" + ui->tab9_2->horizontalHeaderItem(c)->text() + "</th>";
    html += "</tr>";

    for (int r = 0; r < ui->tab9_2->rowCount(); r++) {
        html += "<tr>";
        for (int c = 0; c < ui->tab9_2->columnCount(); c++)
            html += "<td>" + ui->tab9_2->item(r, c)->text() + "</td>";
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

void GestionCreateur::afficher()
{
    QSqlQuery q("SELECT * FROM CREATEUR");
    remplirTableAvecQuery(q);
}

void GestionCreateur::predire()
{
    int row = ui->tab9_2->currentRow();

    if (row < 0) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Veuillez sélectionner un créateur dans le tableau !");
        return;
    }

    QString platform = ui->tab9_2->item(row, 6)->text().trimmed();

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

void GestionCreateur::statistiques()
{
    QSqlQuery q("SELECT RESEAU, SUM(ABONNES) FROM CREATEUR GROUP BY RESEAU");

    QStringList categories;
    QBarSet *barset = new QBarSet("Abonnés");

    while (q.next())
    {
        QString reseau = q.value(0).toString();
        int abonnes = q.value(1).toInt();

        if (reseau.isEmpty())
            reseau = "(vide)";

        categories << reseau;
        *barset << abonnes;
    }

    QBarSeries *series = new QBarSeries();
    series->append(barset);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre d'abonnés par plateforme");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Abonnés");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    QLayout *layout = ui->chartWidget_2->layout();
    if (!layout)
    {
        layout = new QVBoxLayout(ui->chartWidget_2);
        ui->chartWidget_2->setLayout(layout);
    }

    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    layout->addWidget(view);
}

void GestionCreateur::plateformeDominante()
{
    QSqlQuery q("SELECT RESEAU, SUM(ABONNES) FROM CREATEUR GROUP BY RESEAU");

    QString bestPlatform = "";
    int bestValue = -1;

    QString results = "Totaux par plateforme :\n\n";

    while (q.next()) {
        QString reseau = q.value(0).toString();
        int total = q.value(1).toInt();

        results += QString("%1 : %2 abonnés\n").arg(reseau).arg(total);

        if (total > bestValue) {
            bestValue = total;
            bestPlatform = reseau;
        }
    }

    if (bestPlatform.isEmpty()) {
        QMessageBox::warning(nullptr, "Statistique", "Aucune donnée disponible.");
        return;
    }

    QMessageBox::information(
        nullptr,
        "Plateforme dominante",
        QString("Plateforme la plus populaire :\n\n👉 %1 (%2 abonnés)\n\n\n%3")
            .arg(bestPlatform)
            .arg(bestValue)
            .arg(results)
        );
}
