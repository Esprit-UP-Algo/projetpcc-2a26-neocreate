#ifndef COLOR_SENSOR_HANDLER_H
#define COLOR_SENSOR_HANDLER_H

#include <QString>
#include <QColor>
#include <QMap>

struct ColorMatch {
    QString colorName;   // "red", "green", "blue", "yellow"
    QString materielType; // "Casques", "Caméra", "Micros podcast", "Webcam"
    int distance;        // how close the match is (lower = better)
};

class ColorSensorHandler
{
public:
    // Detect which material type matches the RGB values
    static ColorMatch detectMaterial(int r, int g, int b);

    // Get the expected RGB for each material type
    static QMap<QString, QColor> getMaterialColors();

    // Calculate distance between two RGB colors
    static int colorDistance(int r1, int g1, int b1, int r2, int g2, int b2);

private:
    static constexpr int COLOR_THRESHOLD = 120; // tolerance for color matching (adjusted for real sensor variation)
};

#endif // COLOR_SENSOR_HANDLER_H
