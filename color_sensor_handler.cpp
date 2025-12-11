#include "color_sensor_handler.h"
#include <cmath>

ColorMatch ColorSensorHandler::detectMaterial(int r, int g, int b)
{
    const QMap<QString, QColor> colorMap = getMaterialColors();
    ColorMatch best = {"Unknown", "", INT_MAX};

    for (auto it = colorMap.begin(); it != colorMap.end(); ++it) {
        const QString& materialType = it.key();
        const QColor& expected = it.value();

        int dist = colorDistance(r, g, b, expected.red(), expected.green(), expected.blue());

        if (dist < best.distance) {
            best.distance = dist;
            best.colorName = expected.name();
            best.materielType = materialType;
        }
    }

    // If distance is too high, treat as invalid
    if (best.distance > COLOR_THRESHOLD) {
        return {"Invalid", "", INT_MAX};
    }

    return best;
}

QMap<QString, QColor> ColorSensorHandler::getMaterialColors()
{
    QMap<QString, QColor> colors;
    colors["Casques"] = QColor(255, 0, 0);           // Red
    colors["Caméra"] = QColor(0, 255, 0);            // Green
    colors["Micros podcast"] = QColor(0, 0, 255);    // Blue
    colors["Webcam"] = QColor(255, 255, 0);          // Yellow
    return colors;
}

int ColorSensorHandler::colorDistance(int r1, int g1, int b1, int r2, int g2, int b2)
{
    // Euclidean distance in RGB space
    int dr = r1 - r2;
    int dg = g1 - g2;
    int db = b1 - b2;
    return static_cast<int>(std::sqrt(dr*dr + dg*dg + db*db));
}
