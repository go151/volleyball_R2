#ifndef __WS2812_H__
#define __WS2812_H__
#include "main.h" 


#define WS2812_SPI_UNIT     hspi6

// ========== µ∆π‚–Ú∫≈∂®“Â ==========
// µÕ“Ù£®–Ú∫≈ 0~6£©
#define NOTE_L_DO_light   0
#define NOTE_L_RE_light   1
#define NOTE_L_MI_light   2
#define NOTE_L_FA_light   3
#define NOTE_L_SOL_light  4
#define NOTE_L_LA_light   5
#define NOTE_L_SI_light   6

// ÷–“Ù£®–Ú∫≈ 7~13£©
#define NOTE_M_DO_light   7
#define NOTE_M_RE_light   8
#define NOTE_M_MI_light   9
#define NOTE_M_FA_light   10
#define NOTE_M_SOL_light  11
#define NOTE_M_LA_light   12
#define NOTE_M_SI_light   13

// ∏ﬂ“Ù£®–Ú∫≈ 14~20£©
#define NOTE_H_DO_light   14
#define NOTE_H_RE_light   15
#define NOTE_H_MI_light   16
#define NOTE_H_FA_light   17
#define NOTE_H_SOL_light  18
#define NOTE_H_LA_light   19
#define NOTE_H_SI_light   20

#define NOTE_MUTE_light   21


extern SPI_HandleTypeDef WS2812_SPI_UNIT;
extern const uint8_t note_rgb[22][3];
void WS2812_Ctrl_Change(const uint8_t note_rbg[21][3],uint8_t i);
void WS2812_Ctrl(uint8_t r, uint8_t g, uint8_t b);
void LanTingXu_LightChange();
#endif
