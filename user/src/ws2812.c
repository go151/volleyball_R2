#include "ws2812.h"
#include "BUZZER.h"
#define WS2812_LowLevel    0xC0     // 0码
#define WS2812_HighLevel   0xF0     // 1码

// 色相方案：C红、D橙、E黄、F黄绿、G绿、A蓝、B紫
// 亮度系数：低音 0.5，中音 0.75，高音 1.0 （可根据实际光线调整）

const uint8_t note_rgb[22][3] = {
    // 低音 (亮度 ×0.5)
    {128, 0, 0},     // NOTE_L_DO  红
    {128, 64, 0},    // NOTE_L_RE  橙
    {128, 128, 0},   // NOTE_L_MI  黄
    {64, 128, 0},    // NOTE_L_FA  黄绿
    {0, 128, 0},     // NOTE_L_SOL 绿
    {0, 64, 128},    // NOTE_L_LA  蓝
    {128, 0, 128},   // NOTE_L_SI  紫

    // 中音 (亮度 ×0.75)
    {191, 0, 0},     // NOTE_M_DO
    {191, 96, 0},    // NOTE_M_RE
    {191, 191, 0},   // NOTE_M_MI
    {96, 191, 0},    // NOTE_M_FA
    {0, 191, 0},     // NOTE_M_SOL
    {0, 96, 191},    // NOTE_M_LA
    {191, 0, 191},   // NOTE_M_SI

    // 高音 (亮度 ×1.0)
    {255, 0, 0},     // NOTE_H_DO
    {255, 128, 0},   // NOTE_H_RE
    {255, 255, 0},   // NOTE_H_MI
    {128, 255, 0},   // NOTE_H_FA
    {0, 255, 0},     // NOTE_H_SOL
    {0, 128, 255},   // NOTE_H_LA
    {255, 0, 255} ,   // NOTE_H_SI
		{0,0,0}
};

void WS2812_Ctrl(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t txbuf[24];
    uint8_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        txbuf[7-i]  = (((g>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
        txbuf[15-i] = (((r>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
        txbuf[23-i] = (((b>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
    }
    while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY);
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, txbuf, 24,100);

}

void WS2812_Ctrl_Change(const uint8_t note_rbg[22][3],uint8_t i)
{
    uint8_t txbuf[24];
    uint8_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        txbuf[7-i]  = (((note_rbg[i][1]>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
        txbuf[15-i] = (((note_rbg[i][0]>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
        txbuf[23-i] = (((note_rbg[i][2]>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
    }
    while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY);
    HAL_SPI_Transmit_DMA(&WS2812_SPI_UNIT, txbuf, 24);

}

void LanTingXu_LightChange()
{
 if(!MusicFlag1){
	 
   switch(MusicProcessLanTingxu){
switch(MusicProcessLanTingxu) {
    case 0:  WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 1:  WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 2:  WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 3:  WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 4:  WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 5:  WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 6:  WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 7:  WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 8:  WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 9:  WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 10: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 11: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 12: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 13: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 14: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 15: WS2812_Ctrl_Change(note_rgb, NOTE_H_SOL_light); break;
    case 16: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 17: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 18: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 19: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 20: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 21: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 22: WS2812_Ctrl_Change(note_rgb, NOTE_H_SOL_light); break;
    case 23: WS2812_Ctrl_Change(note_rgb, NOTE_H_LA_light);  break;
    case 24: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 25: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 26: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 27: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 28: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 29: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 30: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 31: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 32: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 33: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 34: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 35: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 36: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 37: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 38: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 39: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 40: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 41: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 42: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 43: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 44: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 45: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 46: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 47: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 48: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 49: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 50: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 51: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 52: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 53: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 54: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 55: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 56: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 57: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 58: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 59: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 60: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 61: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 62: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 63: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 64: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 65: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 66: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 67: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 68: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 69: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 70: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 71: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 72: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 73: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 74: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 75: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 76: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 77: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 78: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 79: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 80: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 81: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 82: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 83: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 84: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 85: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 86: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 87: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 88: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 89: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 90: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 91: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 92: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 93: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 94: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 95: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 96: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 97: WS2812_Ctrl_Change(note_rgb, NOTE_L_SI_light);  break;
    case 98: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 99: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 100: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 101: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 102: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 103: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 104: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 105: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 106: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 107: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 108: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 109: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 110: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 111: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 112: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 113: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 114: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 115: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 116: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 117: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 118: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 119: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 120: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 121: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 122: WS2812_Ctrl_Change(note_rgb, NOTE_M_DO_light);  break;
    case 123: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 124: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 125: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 126: WS2812_Ctrl_Change(note_rgb, NOTE_M_RE_light);  break;
    case 127: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 128: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 129: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 130: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 131: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 132: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 133: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 134: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 135: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 136: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 137: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 138: WS2812_Ctrl_Change(note_rgb, NOTE_M_MI_light);  break;
    case 139: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 140: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 141: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 142: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 143: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 144: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 145: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 146: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 147: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 148: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 149: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 150: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 151: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 152: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 153: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 154: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 155: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 156: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 157: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 158: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 159: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 160: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 161: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 162: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 163: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 164: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 165: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 166: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 167: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 168: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 169: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 170: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 171: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 172: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 173: WS2812_Ctrl_Change(note_rgb, NOTE_H_SOL_light); break;
    case 174: WS2812_Ctrl_Change(note_rgb, NOTE_H_SOL_light); break;
    case 175: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 176: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 177: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 178: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 179: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 180: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 181: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 182: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
    case 183: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 184: WS2812_Ctrl_Change(note_rgb, NOTE_H_SOL_light); break;
    case 185: WS2812_Ctrl_Change(note_rgb, NOTE_H_LA_light);  break;
    case 186: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 187: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 188: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 189: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 190: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 191: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 192: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 193: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 194: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 195: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 196: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 197: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 198: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 199: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 200: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 201: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 202: WS2812_Ctrl_Change(note_rgb, NOTE_M_LA_light);  break;
    case 203: WS2812_Ctrl_Change(note_rgb, NOTE_M_SOL_light); break;
    case 204: WS2812_Ctrl_Change(note_rgb, NOTE_H_RE_light);  break;
    case 205: WS2812_Ctrl_Change(note_rgb, NOTE_H_MI_light);  break;
    case 206: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 207: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 208: WS2812_Ctrl_Change(note_rgb, NOTE_H_DO_light);  break;
    case 209: WS2812_Ctrl_Change(note_rgb, NOTE_MUTE_light);  break;
}
	 
	 
	 }
}}





