#pragma once

enum PixelTypes : unsigned char { TOKEN = 64, EDGE = 191, VERTEX = 255, E_POSITIONING = 153, V_POSITIONING = 77, T_POSITIONING = 128 };

class Pixel
{
public:
	Pixel();
	Pixel(const unsigned char R_, const unsigned char G_, const unsigned char B_, const unsigned char Alpha_);
	
	unsigned char getR(void);
	unsigned char getG(void);
	unsigned char getB(void);
	unsigned char getAlpha(void);
	void setR(unsigned char R_);
	void setG(unsigned char G_);
	void setB(unsigned char B_);
	void setAlpha(unsigned char alpha_);

	bool operator==(const Pixel& pix);
	
	~Pixel();

private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char alpha;

};

