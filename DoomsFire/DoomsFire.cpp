#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

namespace doomfire
{
	const int width = 80;
	const int height = 80;
	const int red = 255;
	const int totalPositions = width * height;
	std::array<int, totalPositions> pixelMap;

	void initialize()
	{
		const int lastLine = (width * (height - 1));
		for (int i = lastLine; i < totalPositions; i++)
			pixelMap[i] = red;
	}

	void print()
	{
		for (int position = 0; position < totalPositions; position++)
		{
			if (position % width == 0 and position > 0)
				std::cout << std::endl;
			std::cout << pixelMap[position] << " ";
		}
		std::cout << std::endl;
	}

	void calculate() {

		for (int position = 0; position < totalPositions; position++)
		{
			int decay = rand() % height;
			const int offset = width;
			const int botPos = (position + rand() % height) + offset;


			if (botPos >= totalPositions)
				continue;
			int nextValue = pixelMap[botPos] - decay;
			if (nextValue < 0)
				nextValue = 0;
			pixelMap[position] = nextValue;
		}

	}

}

class DoomsFireRender : public olc::PixelGameEngine
{
public:
	DoomsFireRender()
	{
		sAppName = "Doom";
	}

public:
	bool OnUserCreate() override
	{
		doomfire::initialize();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int x = 0; x < ScreenWidth(); x++)
		{
			for (int y = 0; y < ScreenHeight(); y++)
			{
				int position = (doomfire::width * y) + x;
				int pix = doomfire::pixelMap[position];
				Draw(x, y, olc::Pixel(pix, 0, 0));
			}
		}
		doomfire::calculate();
		return true;
	}
};


int main()
{
	DoomsFireRender doomsFire;
	if (doomsFire.Construct(doomfire::width, doomfire::height, 4, 4))
		doomsFire.Start();

    	return 0;
}
