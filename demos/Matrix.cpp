#include "ConsolaProd.h"

struct sLine
{
	int length;
	def::vf2d pos;
};

class Matrix : public def::ConsolaProd
{
public:
	Matrix()
	{
		sAppName = L"Matrix";
	}

protected:
	virtual bool OnUserCreate() override
	{
		return true;
	}

	virtual bool OnUserUpdate(float fDeltaTime) override
	{
		Clear(def::Pixel::SOLID, def::FG::BLACK | def::BG::BLACK);

		for (int i = 0; i < GetScreenWidth(); i++)
		{
			if (rand() % 1000 == 0)
				vecLines.push_back({ rand() % 10, { (float)i, 0.0f } });
		}

		for (auto it = vecLines.begin(); it < vecLines.end(); it++)
		{
			if (it->pos.y >= GetScreenHeight())
				it = vecLines.erase(it);

			DrawLine(it->pos.x, it->pos.y, it->pos.x, it->pos.y + it->length, L'X', def::FG::GREEN);
			Draw(it->pos.x, it->pos.y + it->length - 1, L'X', def::FG::DARK_GREEN);
			Draw(it->pos.x, it->pos.y + it->length, L'X', def::FG::DARK_GREY);

			vecLines[std::distance(vecLines.begin(), it)].pos.y += 5.0f * fDeltaTime;
		}

		return true;
	}

private:
	std::vector<sLine> vecLines;
};

int main()
{
	Matrix demo;
	def::rcode err = demo.ConstructConsole(120, 30, 8, 16);

	if (err.ok)
		demo.Run();
	else
		std::cerr << err.info << "\n";

	return 0;
}
