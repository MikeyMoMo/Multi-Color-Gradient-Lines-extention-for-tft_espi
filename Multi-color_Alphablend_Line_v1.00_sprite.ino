#include <TFT_eSPI.h>  // Make sure to have this configured
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite mBlendSprite   = TFT_eSprite(&tft);
TFT_eSprite BackupSprite   = TFT_eSprite(&tft);

struct ColorStage {
  uint16_t startColor;
  uint16_t endColor;
  int length; // in pixeldrawMultiBlendLine2s
};
// Define your multiblend segments here
ColorStage blendSequence[] = {
  {TFT_RED, TFT_ORANGE, 40},
  {TFT_ORANGE, TFT_YELLOW, 40},
  {TFT_YELLOW, TFT_GREEN, 40},
  {TFT_GREEN, TFT_BLUE, 40},
  {TFT_BLUE, TFT_YELLOW, 40}
};
int blendCt = sizeof(blendSequence) / sizeof(blendSequence[0]);
int i;
bool doDebugPrints;
/***************************************************************************/
void setup()
/***************************************************************************/
{
  int *a;

  Serial.begin(115200); delay(4000);
  Serial.println("This is the multi-color gradient line demo.");
  Serial.println("Running from:");
  Serial.println(__FILE__);

  tft.init();
  tft.setRotation(3); // Adjust as needed
  a = (int*)mBlendSprite.createSprite(tft.width(), tft.height());
  if (a == 0) {
    Serial.println("mBlendSprite creation failed.  Cannot continue.");
    while (1);
  }
  a = (int*)BackupSprite.createSprite(tft.width(), tft.height());
  if (a == 0) {
    Serial.println("BackupSprite creation failed.  Cannot continue.");
    while (1);
  }
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  mBlendSprite.setTextDatum(TC_DATUM);
}
/***************************************************************************/
void loop()
/***************************************************************************/
{
  // Proof of concept section
  tft.fillScreen(TFT_BLACK);
  mBlendSprite.fillSprite(TFT_BLACK);
  tft.drawString("Drawing lines...",
                 tft.width() / 2, tft.height() / 2, 4);
  if (doDebugPrints)
    Serial.println("\r\n<****************************************>\r\n");

  if (doDebugPrints)
    Serial.println("<-Slope down-right original ----------------->\r\n");
  drawMultiBlendLine(&mBlendSprite, 10, 10, 210, 110, blendSequence,
                     blendCt);

  if (doDebugPrints)
    Serial.println("<-Slope down-right longer ------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, 10, 30, 300, 210, blendSequence,
                      blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Slope down-right longer ------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, 10, 50, 210, 210, blendSequence,
                      blendCt, false);

  if (doDebugPrints)
    Serial.println("<-The original three ------------------------>\r\n");
  mBlendSprite.pushToSprite(&BackupSprite, 0, 0);  // Save it before
  mBlendSprite.drawString("The first three.",
                          tft.width() / 2, 0, 4);
  mBlendSprite.setTextDatum(BC_DATUM);
  mBlendSprite.drawString("Waiting 4 secs...",
                          tft.width() / 2, tft.height(), 4);
  mBlendSprite.setTextDatum(TC_DATUM);

  mBlendSprite.pushSprite(0, 0);  // As the teachers say... SHOW YOUR WORK!
  delay(4000);
  BackupSprite.pushToSprite(&mBlendSprite, 0, 0);  // Put back the original.

  if (doDebugPrints)
    Serial.println("<-Slope down-right v2 ----------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, 0, tft.height() / 4,
                      tft.width(), tft.height() / 4,
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Vertical down at 1/4 ---------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, tft.width() / 4, 0,
                      tft.width() / 4, tft.height(),
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Horizontal to left at .75 ----------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, tft.width(), tft.height() * 0.75,
                      0, tft.height() * 0.75,
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Vertical upwards at .75 ------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, tft.width() * 0.75, tft.height(),
                      tft.width() * 0.75, 0,
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Horizontal to the left at .75 ------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, tft.width(), tft.height() * 0.75,
                      0, tft.height() * 0.75,
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Upwards to the left ----------------------->\r\n");
  doDebugPrints = false;
  drawMultiBlendLine2(&mBlendSprite, tft.width(), tft.height() * 0.75, 0, 0,
                      blendSequence, blendCt, true);

  if (doDebugPrints)
    Serial.println("<-Random ------------------------------------>\r\n");
  doDebugPrints = false;
  for (i = 0; i < 5; i++)
    drawMultiBlendLine2(&mBlendSprite,
                        random(tft.width()), random(tft.height()),
                        random(tft.width()), random(tft.height()),
                        blendSequence, blendCt, true);

  mBlendSprite.drawString("Done.", tft.width() / 2, 0, 4);
  mBlendSprite.pushSprite(0, 0);  // As the teachers say... SHOW YOUR WORK!
  delay(5000);
}
/***************************************************************************/
void drawMultiBlendLine(TFT_eSPI* targetPallete,
                        int x, int y, int dx, int dy, ColorStage* stages,
                        int numStages)
/***************************************************************************/
{
  /*
     There is something unusual that needs to be explained.
     dx and dy do not specify the end of the line.  The end of the line
     is computed as it goes along.  dx and dy are used to get the slope
     of the line.  The length will be the sum of the color segments'
     length values in the struct.
  */

  if (doDebugPrints)
    Serial.printf("Orig Called with x %i, y %i, dx %i, dy %i\r\n",
                  x, y, dx, dy);
  float angle = atan2(dy - y, dx - x);
  float curX = x;
  float curY = y;
  uint16_t blended;
  float ratio;

  for (int i = 0; i < numStages; i++) {
    for (int j = 0; j < stages[i].length; j++) {
      ratio = (float)j / (float)stages[i].length;
      blended = alphaBlend(ratio * 255, stages[i].startColor,
                           stages[i].endColor);
      if (doDebugPrints)
        Serial.printf("x %i, y %i, i %i, j %i blended %lu\r\n",
                      int(curX), int(curY), i, j, blended);
      targetPallete->drawPixel((int)curX, (int)curY, blended);
      curX += cos(angle);
      curY += sin(angle);
    }
  }
}
/***************************************************************************/
uint16_t alphaBlend(uint8_t alpha, uint16_t bgc, uint16_t fgc)
/***************************************************************************/
{
  uint32_t rxb = bgc & 0xF81F;
  rxb += ((fgc & 0xF81F) - rxb) * (alpha >> 2) >> 6;
  uint32_t xgx = bgc & 0x07E0;
  xgx += ((fgc & 0x07E0) - xgx) * alpha >> 8;
  return (rxb & 0xF81F) | (xgx & 0x07E0);
}
/***************************************************************************/
void drawMultiBlendLine2(TFT_eSPI* targetPallete,
                         int x0, int y0, int x1, int y1,
                         ColorStage* stages, int numStages,
                         bool honorLineLength)
/***************************************************************************/
{
  float dx = x1 - x0;
  float dy = y1 - y0;
  float actualLength = sqrt(dx * dx + dy * dy);
  float angle = atan2(dy, dx);
  float stepX = cos(angle);
  float stepY = sin(angle);
  int fillX, fillY;
  float scale = 1.0;

  if (doDebugPrints)
    Serial.printf("Ver2 Called with x %i, y %i, dx %i, dy %i\r\n",
                  x0, y0, x1, y1);
  if (doDebugPrints)
    Serial.printf("stepX %.2f, stepY %.2f\r\n", stepX, stepY);
  int blendLength = 0;
  for (int i = 0; i < numStages; i++) blendLength += stages[i].length;

  if (honorLineLength && blendLength > 0)
    scale = actualLength / blendLength;

  float curX = x0;
  float curY = y0;

  for (int i = 0; i < numStages; i++) {
    for (int j = 0; j < stages[i].length; j++) {
      float ratio = (float)j / stages[i].length;
      uint16_t blended = alphaBlend(ratio * 255, stages[i].startColor,
                                    stages[i].endColor);
      if (doDebugPrints)
        Serial.printf("Orig: x %i, y %i, i %i, j %i, "
                      "scale %.2f, blended %lu\r\n",
                      int(curX), int(curY), i, j, scale, blended);
      targetPallete->drawPixel((int)curX, (int)curY, blended);
      fillX = int(curX); fillY = int(curY);
      curX += stepX * scale;
      curY += stepY * scale;

      /*
        Now, it is time to fill in the holes.  If the scale, stepX or
        stepY are greater than 1.0 then there will be holes left in
        the line if it is not orthogonal.  So I have to check curX
        and curY to see if they stepped more than one and go back and
        fill in the missing pixels.
      */

      // Ver 0.06 version
      while (int(curX) != fillX || int(curY) != fillY) {
        if (int(curX) > fillX) {
          fillX += 1.0;
          if (doDebugPrints)
            Serial.printf("FillX+: x %i, y %i, i %i, j %i, "
                          "scale %.2f, blended %lu\r\n",
                          fillX, int(curY), i, j, scale, blended);
          targetPallete->drawPixel((int)fillX, (int)curY, blended);
        }
        if (int(curX) < fillX) {
          fillX -= 1.0;
          if (doDebugPrints)
            Serial.printf("FillY+: x %i, y %i, i %i, j %i, "
                          "scale %.2f, blended %lu\r\n",
                          fillX, int(curY), i, j, scale, blended);
          targetPallete->drawPixel(fillX, (int)curY, blended);
        }

        if (int(curY) > fillY) {
          fillY += 1.0;
          if (doDebugPrints)
            Serial.printf("FillX-: x %i, y %i, i %i, j %i, "
                          "scale %.2f, blended %lu\r\n",
                          fillX, int(curY), i, j, scale, blended);
          targetPallete->drawPixel(fillX, (int)curY, blended);
        }
        if (int(curY) < fillY) {
          fillY -= 1.0;
          if (doDebugPrints)
            Serial.printf("FillY-: x %i, y %i, i %i, j %i, "
                          "scale %.2f, blended %lu\r\n",
                          fillX, int(curY), i, j, scale, blended);
          targetPallete->drawPixel((int)fillX, (int)curY, blended);
        }
      }
    }
  }
}
