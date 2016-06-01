#ifndef CRC
#define CRC

const int PolyNum = 0x50;

static inline byte CRC8(byte data, byte poly)
{
    for (int i = 0; i < 8; ++i)
    {
        poly = poly << 1;
        int bit = (data >> i) & 1;
        if (bit)
        {
            poly = poly ^ PolyNum;
        }
    }

    return poly;
}

#endif // CRC
