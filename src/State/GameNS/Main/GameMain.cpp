#include "GameMain.h"
#include "../../../KeyInput.h"
#include"../ClearOver.h"
#include "Object/DynamicObj/Player.h"
#include "Object/DynamicObj/Enemy.h"
#include "Object/Castle.h"
#include "Object/Item.h"

namespace StateNS {
	namespace GameStateNS {


		GameMain::GameMain(int diff) {
			difficult = diff;

			player = new Player(difficult);
			for (float i = -150.0f; i <= 150.0f; i += 150.0f) {
				for (float j = -150.0f; j <= 150.0f; j += 150.0f) {
					if (i == 0.0f && j == 0.0f)continue;
					enemy.push_back(new Enemy(i - 30.0f + (float)GetRand(60), 0.0f, j - 30.0f + (float)GetRand(60), 5.0f, 15.0f, 5.0f));
				}
			}

			castle = new Castle();

			item.push_back(new Item(150.0f, 0.0f, 150.0f));
			item.pop_back();

			if (difficult == 0) {
				item.push_back(new Item(-15.0f, 0.0f, -30.0f));
				item.push_back(new Item(15.0f, 0.0f, -30.0f));
			}
			if(difficult==0 || difficult==1)item.push_back(new Item(0.0f, 0.0f, 30.0f));


			time = 60;
			count_start = 0;
			count_play = 0;
			count_finish = 0;

			img_number[0] = LoadGraph("Data/image/number/0.png");
			img_number[1] = LoadGraph("Data/image/number/1.png");
			img_number[2] = LoadGraph("Data/image/number/2.png");
			img_number[3] = LoadGraph("Data/image/number/3.png");
			img_number[4] = LoadGraph("Data/image/number/4.png");
			img_number[5] = LoadGraph("Data/image/number/5.png");
			img_number[6] = LoadGraph("Data/image/number/6.png");
			img_number[7] = LoadGraph("Data/image/number/7.png");
			img_number[8] = LoadGraph("Data/image/number/8.png");
			img_number[9] = LoadGraph("Data/image/number/9.png");
			img_call[0] = LoadGraph("Data/image/number/start.png");
			img_call[1] = LoadGraph("Data/image/number/finish.png");
			img_icon[0] = LoadGraph("Data/image/player.png");
			img_icon[1] = LoadGraph("Data/image/castle.png");
			HPicon = LoadGraph("Data/image/HP.png");

			ModelHandle_floor = MV1LoadModel("Data/model/sunahama/sunahama.pmx");
			//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
			// 指定位置にモデルを配置
			MV1SetPosition(ModelHandle_floor, VGet(0, 0, 0));

			SetCameraNearFar(15.0f, 1500.0f);
			stage = STAGE_start;
			gameclear = true;

			se[0] = LoadSoundMem("Data/music/se/se_maoudamashii_system47.wav");//スタートまでのカウントダウン
			se[1] = LoadSoundMem("Data/music/se/se_maoudamashii_se_whistle01.wav");//スタートコール
			bgm = LoadSoundMem("Data/music/play/game_maoudamashii_1_battle11.mp3");
			deadenemyCount = 0;

		}


		GameMain::~GameMain() {
			for (auto v : enemy) {
				SAFE_DELETE(v);
			}
			SAFE_DELETE(player);
			SAFE_DELETE(castle);
			for (auto v : item) {
				SAFE_DELETE(v);
			}

		}

		GameChild* GameMain::update(GameParent *parent) {
			GameChild *next = this;

			switch (stage) {
			case STAGE_start:

				if (count_start % 60 == 0 && count_start < 180)PlaySoundMem(se[0], DX_PLAYTYPE_BACK);
				if (count_start == 180)PlaySoundMem(se[1], DX_PLAYTYPE_BACK);
				if (count_start == 240) {
					PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
					stage = STAGE_play;
				}
				count_start++;
				break;
			case STAGE_play:
				count_play++;
				play_update();
				if (castle->getHP() == 0) {
					gameclear = false;
					stage = STAGE_finish;
				}
				if (time == 0) {
					gameclear = true;
					stage = STAGE_finish;
				}
				if (player->deadcount() == 120) {
					SAFE_DELETE(player);
					player = new Player(difficult);
				}
				break;
			case STAGE_finish:
				count_finish++;
				if (count_finish == 120) {
					StopSoundMem(bgm);
					if (gameclear)next = new Clear();
					else next = new Over();
				}
				break;
			}
			return next;
		}

		void GameMain::play_update() {
			if (count_play % 60 == 0)time--;

			if(deadenemyCount>30)deadenemyCount = 30;
			if (count_play % (330 - deadenemyCount * 3*(difficult+1)) == 0) {
				for (float i = -150.0f; i <= 150.0f; i += 150.0f) {
					for (float j = -150.0f; j <= 150.0f; j += 150.0f) {
						if (i == 0.0f && j == 0.0f)continue;
						if (GetRand(100) % (4-difficult )== 0)enemy.push_back(new Enemy(i - 30.0f + (float)GetRand(60), 0.0f, j - 30.0f + (float)GetRand(60), 5.0f, 15.0f, 5.0f));
					}
				}
			}
			//update
			player->update();
			for (auto itr = item.begin(); itr != item.end();) {
				player->getCollision()->update((*itr));
				if ((*itr)->isDelete()) {
					delete *itr;
					itr = item.erase(itr);
					continue;
				}
				++itr;

			}


			castle->update();
			for (auto itr = enemy.begin(); itr != enemy.end();) {

				player->getCollision()->update((*itr));
				castle->getCollision()->update((*itr));
				for (auto v : (*itr)->getATKlist()) {
					player->getCollision()->update(v);
					castle->getCollision()->update(v);
				}
				(*itr)->update(player);
				(*itr)->getCollision()->update(player);
				(*itr)->getCollision()->update(castle);

				for (auto v : player->getATKlist()) {
					(*itr)->getCollision()->update(v);
				}

				if ((*itr)->isDelete()) {
					if (GetRand(100) % (4-difficult) == 0)item.push_back(new Item((*itr)->get_x(), (*itr)->get_y(), (*itr)->get_z()));
					deadenemyCount++;
					delete *itr;
					itr = enemy.erase(itr);
					continue;
				}
				++itr;

			}

		}

		void GameMain::draw() const {
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "GameMain");
			MV1DrawModel(ModelHandle_floor);

			player->draw();
			//	DrawFormatString(100, 100, GetColor(255, 255, 255), "%f:%f", player->get_x(), player->get_z());
			castle->draw();
//			DrawFormatString(0, 400, GetColor(0, 0, 0), "%d", deadenemyCount);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(503, 352, 604, 453, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawBox(550 + player->get_x() / 2, 400 - player->get_z() / 2, 560 + player->get_x() / 2, 410 - player->get_z() / 2, GetColor(0, 255, 0), TRUE);

			for (auto v : item) {
				v->draw();
				DrawBox(550 + v->get_x() / 2, 400 - v->get_z() / 2, 560 + v->get_x() / 2, 410 - v->get_z() / 2, GetColor(255, 255, 0), TRUE);
			}
			for (auto v : enemy) {
				v->draw();
				DrawBox(550 + v->get_x() / 2, 400 - v->get_z() / 2, 560 + v->get_x() / 2, 410 - v->get_z() / 2, GetColor(255, 0, 0), TRUE);
			}
			switch (stage) {
			case STAGE_start:
				if (count_start < 180) DrawRotaGraph(cx, cy, 1.0f, 0.0f, img_number[3 - count_start / 60], TRUE);
				else DrawRotaGraph(cx, cy, 1.0f, 0.0f, img_call[0], TRUE);
				break;
			case STAGE_play:
				//DrawFormatString(500, 0, GetColor(255, 255, 255), "残り%d秒", time);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawRotaGraph(520, 70, 1.0f, 0.0f, img_number[time / 10], TRUE);
				DrawRotaGraph(600, 70, 1.0f, 0.0f, img_number[time % 10], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				//城HP
				//DrawFormatString(0, 0, GetColor(255, 255, 255), "CastleHP");
				DrawRotaGraph(20, 30, 0.1f, 0.0f, img_icon[1], TRUE);
				DrawBox(35, 20, 35 + 150 * (castle->getHP() / (float)castle->getMAXHP()), 40, GetColor(0, 255, 0), TRUE);
				DrawBox(35, 20, 185, 40, GetColor(255, 255, 255), FALSE);
				//自機HP
				//DrawFormatString(0, 40, GetColor(255, 255, 255), "PlayerHP");
				DrawRotaGraph(20, 70, 0.1f, 0.0f, img_icon[0], TRUE);
				for (int i = 0; i < player->getHP() / 100; i++) {
					DrawRotaGraph(50 + i * 30, 70, 0.1f, 0.0f, HPicon, TRUE);
				}
				//DrawBox(35, 62, 35 + 150 * (player->getHP() / (float)player->getMAXHP()), 82, GetColor(0, 255, 0), TRUE);
				//DrawBox(35, 62, 185, 82, GetColor(255, 255, 255), FALSE);
				break;
			case STAGE_finish:
				DrawRotaGraph(cx, cy, 1.0f, 0.0f, img_call[1], TRUE);
				break;
			}

		}
	}
}
namespace StateNS {
namespace GameStateNS {


		Tutorial::Tutorial() {

			player = new Player(1);
			castle = new Castle();

			ModelHandle_floor = MV1LoadModel("Data/model/sunahama/sunahama.pmx");
			//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
			// 指定位置にモデルを配置
			MV1SetPosition(ModelHandle_floor, VGet(0, 0, 0));


			bgm = LoadSoundMem("Data/music/explain/raribou.mp3");
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
			SetCameraNearFar(15.0f, 1500.0f);


		}


		Tutorial::~Tutorial() {
			SAFE_DELETE(player);
			SAFE_DELETE(castle);

		}

		GameChild* Tutorial::update(GameParent *parent) {
			GameChild *next = this;
			player->update();
			castle->update();
			if (Input_BACK()||Input_C()) {
				StopSoundMem(bgm);
				parent->moveTo(parent->NextSeq::SEQ_TITLE);
			}
			return next;
		}


		void Tutorial::draw() const {
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "Tutorial");
			MV1DrawModel(ModelHandle_floor);

			player->draw();
			//	DrawFormatString(100, 100, GetColor(255, 255, 255), "%f:%f", player->get_x(), player->get_z());
			castle->draw();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(503, 352, 604, 453, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawBox(550 + player->get_x() / 2, 400 - player->get_z() / 2, 560 + player->get_x() / 2, 410 - player->get_z() / 2, GetColor(0, 255, 0), TRUE);

			DrawFormatString(30, 30, GetColor(0, 0, 0), "移動:");
			DrawFormatString(30, 60, GetColor(0, 0, 0), "十字キー　または　W,A,S,Dキー");

			DrawFormatString(30, 120, GetColor(0, 0, 0), "弾を撃つ:");
			DrawFormatString(30, 150, GetColor(0, 0, 0), "Zキー　または　Enterキー");

			DrawFormatString(30, 210, GetColor(0, 0, 0), "ジャンプ:");
			DrawFormatString(30, 240, GetColor(0, 0, 0), "SPACEキー");

			DrawFormatString(440, 30, GetColor(0, 0, 0), "そうさせつめいを終わる:");
			DrawFormatString(440, 60, GetColor(0, 0, 0), "BackSpaceキー");

		

		}
	
}
}
