#include "Rank.h"

void Rank::SaveRank(string name, int score, int stage)
{
	ofstream Save;
	Save.open("Rank.txt", ios::app);
	if (Save.is_open())
	{
		Save << name << " ";
		Save << score << " ";
		Save << stage << " ";
		Save << endl;
		Save.close();
	}
}

int Rank::LoadRank()
{
	ifstream Load;
	Load.open("Rank.txt");

	if (!Load.is_open())
	{
		return 0;
	}
	else
	{
		while (!Load.eof())
		{
			Data LoadData;
			Load >> LoadData.PlayerName;
			Load >> LoadData.Score;
			Load >> LoadData.Stage;
			if (LoadData.PlayerName == "")
				break;
			Records.push_back(LoadData);
		}
		return 1;
	}
	Load.close();
}

bool comp(Data d1, Data d2)
{
	//return (d1.Stage > d2.Stage) ? true : ((d1.Score > d2.Score) ? true : false);
	if (d1.Stage > d2.Stage)
		return true;
	else if (d1.Stage == d2.Stage)
	{
		if (d1.Score > d2.Score)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Rank::ShowRank()
{
	if (LoadRank() == 1)
	{
		system("cls");
		Draw::BoxDraw(0, 0, WIDTH, HEIGHT);
		Draw::BoxDraw((WIDTH*0.5) - 10, (HEIGHT*0.2) - 2, (WIDTH * 0.5) + 10, (HEIGHT*0.2) + 2);
		Draw::DrawMidText("Ranking", WIDTH, HEIGHT*0.2);
		Draw::DrawMidText("=================================================================================================", WIDTH, HEIGHT*0.3);
		Draw::DrawPoint("Name", 10, HEIGHT*0.4);
		Draw::DrawPoint("Score", WIDTH/2, HEIGHT*0.4);
		Draw::DrawPoint("Stage", WIDTH -10, HEIGHT*0.4);

		sort(Records.begin(), Records.end(), comp);
		vector<Data> Top10Records;


		for (auto iter = Records.begin(); iter != Records.end(); iter++)
		{
			if (Top10Records.size() < 10)
				Top10Records.push_back(*iter);
			else break;
		}

		int i = 1;
		for (auto iter = Top10Records.begin(); iter != Top10Records.end(); iter++)
		{
			Draw::DrawPoint(iter->PlayerName, 10, HEIGHT*0.4 +i);
			Draw::DrawPoint(to_string(iter->Score), WIDTH/2, HEIGHT*0.4 + i);
			Draw::DrawPoint(to_string(iter->Stage), WIDTH - 10, HEIGHT*0.4 + i);
			i++;
		}
		getch();
		Top10Records.clear();
		Records.clear();
	}
	else
		Draw::DrawMidText("랭킹정보데이터없음", WIDTH, HEIGHT*0.2);
}

void Rank::ClearRankData()
{
	if (Records.size() != NULL)
		Records.clear();	
}
