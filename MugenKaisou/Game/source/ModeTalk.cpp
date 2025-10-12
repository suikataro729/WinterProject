
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTalk.h"
#include "utf8sjis.h"	// jsonの日本語文字を使うために必要
#include	<cassert>
#include	<string>

ModeTalk::ModeTalk(std::string TextHandle ,bool Cristmas){
	// jsonファイルの読み込み
	std::ifstream file(TextHandle);
	nlohmann::json json;
	file >> json;
	int i = 0;
	// データを読み込む
	for (auto jsonfile : json)
	{
		jsonfile.at("message1").get_to(_jsonData[i].message1);
		jsonfile.at("chara").get_to(_jsonData[i].draw);
		jsonfile.at("charaX").get_to(_jsonData[i].drawX);
		jsonfile.at("charaY").get_to(_jsonData[i].drawY);
		jsonfile.at("command").get_to(_jsonData[i].command);
		jsonfile.at("name").get_to(_jsonData[i].name);
		jsonfile.at("voice").get_to(_jsonData[i].voice);
		jsonfile.at("bgY").get_to(_jsonData[i].bgY);
		jsonfile.at("bg").get_to(_jsonData[i].bg);

		// jsonの文字列を、UTF-8からShift-JISに変換
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		_jsonData[i].bg = ConvUTF8toSJIS(_jsonData[i].bg);
		i++;
	}
	messagecnt = 0;
	gameCnt = 0;
	_cgBg = 0;
	text_flg = 0;
	cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
	_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
	cg_MessageBox[0] = LoadGraph("res/Talkart/TalkUI/UI_M.png");
	cg_MessageBox[1] = LoadGraph("res/Talkart/TalkUI/UI_R.png");
	cg_MessageBox[2] = LoadGraph("res/Talkart/TalkUI/UI_L.png");

	gameCnt = 0;
	save_cgChara[0] = 0;
	save_cgChara[1] = 0;
	saveMessage[0] = "";
	saveMessage[1] = "";

	ChrismasTime = 0;
	// クリスマス部屋用にする
	ChrismasFlg = Cristmas;
}
ModeTalk::~ModeTalk() {

}
bool ModeTalk::Initialize() {


	return true;
}

bool ModeTalk::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (ChrismasFlg) {
		// ボタンが押されたら次のテキストへ
		if (text_flg && ChrismasTime > 60) {
			ChrismasTime = 0;
			messagecnt++;
			cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
			//_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
			gameCnt = 0;
			popupflg = false;
			//コマンド別の読み込み
			switch (_jsonData[messagecnt].command) {
			case 1:
				saveMessage[0] = _jsonData[messagecnt].message1;
				save_cgChara[1] = LoadGraph(_jsonData[messagecnt].draw.c_str());
				save_drawX[1] = _jsonData[messagecnt].drawX;
				save_drawY[1] = _jsonData[messagecnt].drawY;
				break;
			case 2:
				saveMessage[1] = _jsonData[messagecnt].message1;
				save_cgChara[0] = LoadGraph(_jsonData[messagecnt].draw.c_str());
				save_drawX[0] = _jsonData[messagecnt].drawX;
				save_drawY[0] = _jsonData[messagecnt].drawY;
				break;
			case 6:
				cg_popup = LoadGraph(_jsonData[messagecnt].draw.c_str());
				popupflg = true;
				popup_size = 0.0f;
				break;
			case 10:
				// このモードを削除する
				ModeServer::GetInstance()->Del(this);
				break;
			}

		}
		else if (text_flg && ChrismasTime <= 60)
		{
			ChrismasTime++;
		}
	}
	else
	{
		// このモードより下のレイヤーはProcess()を呼ばない
		ModeServer::GetInstance()->SkipProcessUnderLayer();
		if (_jsonData[messagecnt + 1].command == 50)
		{
			if (trg & PAD_INPUT_1)
			{
				chengeRoom = 1;
				// このモードを削除する
				ModeServer::GetInstance()->Del(this);
			}
			if (trg & PAD_INPUT_3)
			{
				chengeRoom = 2;
				// このモードを削除する
				ModeServer::GetInstance()->Del(this);
			}
		}
		// ボタンが押されたら次のテキストへ
		else if (trg & PAD_INPUT_2){
			if (text_flg) {
				messagecnt++;
				cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
				_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
				gameCnt = 0;
				popupflg = false;
				//コマンド別の読み込み
				switch (_jsonData[messagecnt].command) {
				case 1:
					saveMessage[0] = _jsonData[messagecnt].message1;
					save_cgChara[1] = LoadGraph(_jsonData[messagecnt].draw.c_str());
					save_drawX[1] = _jsonData[messagecnt].drawX;
					save_drawY[1] = _jsonData[messagecnt].drawY;
					break;
				case 2:
					saveMessage[1] = _jsonData[messagecnt].message1;
					save_cgChara[0] = LoadGraph(_jsonData[messagecnt].draw.c_str());
					save_drawX[0] = _jsonData[messagecnt].drawX;
					save_drawY[0] = _jsonData[messagecnt].drawY;
					break;
				case 6:
					cg_popup = LoadGraph(_jsonData[messagecnt].draw.c_str());
					popupflg = true;
					popup_size = 0.0f;
					break;
				case 10:
					// このモードを削除する
					ModeServer::GetInstance()->Del(this);
					break;
				}

			}
			else
			{
				text_flg = 1;
			}
		}

	}

	int i = messagecnt;
	// 会話パート処理
	const char* Message1_String = _jsonData[messagecnt].message1.c_str();

	if (gameCnt == 0) {
		//カウント系の初期化
		drawCnt1 = 0;
		text_flg = 0;
		text_alpha = 0;
		//画像・音声読み込み
		//if (!popupflg) { cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str()); }
		DeleteSoundMem(se_voice);
		se_voice = LoadSoundMem(_jsonData[messagecnt].voice.c_str());
		PlaySoundMem(se_voice, DX_PLAYTYPE_BACK);
	}

	if (_jsonData[messagecnt].command == 0 ||
		_jsonData[messagecnt].command == 1 ||
		_jsonData[messagecnt].command == 2) {
		if (gameCnt % DRAW_STRING_COUNT == DRAW_STRING_COUNT - 1) {
			int CharBytes;
			if (Message1_String[drawCnt1] != '\0')
			{
				CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message1_String[drawCnt1]);
				drawCnt1 += CharBytes;		// 描画カウンタ
			}
			else
			{
				text_flg = 1;
			}
		}
	}

	float pop_maxsize = 1.0;
	if (text_flg == 0) {
		//アイテムポップアップ
		if (popupflg == 1) {
			//ポップアップのサイズ上昇
			if (popup_size < pop_maxsize) {
				popup_size += 0.07;
				if (popup_size > pop_maxsize) {
					popup_size = pop_maxsize;
					text_flg = 1;
				}
			}
		}
		//drawcnt分の文字出力
		drawMessage1 = _jsonData[i].message1.substr(0, drawCnt1);
	}
	else
	{
		//ポップアップ最大
		popup_size = pop_maxsize;
		//すべての文字出力
		drawMessage1 = _jsonData[i].message1;
	}
	gameCnt++;
	return true;
}

bool ModeTalk::Render() {
	base::Render();
	int Font = GetFontSize();
	SetFontSize(128);
	DrawGraph(0, 0, _cgBg, FALSE); //背景
	int massagefontsize;	//フォントサイズ
	massagefontsize = 28;		//フォントサイズ
	int namefontsize;
	int savefontsize;
	int zurasi = -10;
	savefontsize = GetFontSize();	//元のフォントサイズを保存
	switch (_jsonData[messagecnt].command) {
	case 0:
		//中央
		//一枚絵の画像
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(472, 844, cg_MessageBox[0], TRUE);
		SetFontSize(massagefontsize);
		DrawFormatString(644, 900, GetColor(255, 255, 255), drawMessage1.c_str());							//セリフ描画
		SetFontSize(Font);
		break;
	case 1:
		//左
		//-----------メッセージ読み込み----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0) {
			DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//セーブキャラ描画
			DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//メッセージボックス描画
			DrawFormatString(1098 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//左側セーブセリフ描画
		}
		//薄黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//
		//一枚絵の画像
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//メッセージボックス描画
		DrawFormatString(165 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());							//セリフ描画
		SetFontSize(Font);
		break;
	case 2:
		//右
		//-----------メッセージ読み込み----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0)
		{
			DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//セーブキャラ描画
			DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//メッセージボックス描画
			DrawFormatString(165 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());						//右側セーブセリフ描画
		}

		//薄黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//
		//一枚絵の画像
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);															//メッセージボックス描画
		DrawFormatString(1098 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());				//セリフ描画

		SetFontSize(Font);
		break;
	case 3:
		//左
		//-----------メッセージ読み込み----------------
		SetFontSize(massagefontsize);
		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//セーブキャラ描画
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//メッセージボックス描画
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//左側セーブセリフ描画
		//一枚絵の画像
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//メッセージボックス描画
		DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());							//セリフ描画
		SetFontSize(Font);
		break;
	case 4:
		//右
		//-----------メッセージ読み込み----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0) {
			DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//セーブキャラ描画
			DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//メッセージボックス描画
			DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());						//右側セーブセリフ描画
		}

		//一枚絵の画像
		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//セーブキャラ描画
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//メッセージボックス描画
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//左側セーブセリフ描画

		SetFontSize(Font);
		break;
	case 6:
		//両方暗く
		//-----------メッセージ読み込み----------------

		SetFontSize(massagefontsize);


		DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//セーブキャラ描画
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//メッセージボックス描画
		DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());				//右側セーブセリフ描画

		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//セーブキャラ描画
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//メッセージボックス描画
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());				//左側セーブセリフ描画

		//薄黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
	//アイテムポップアップ
	if (popupflg == 1) {
		//薄黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(960, 420, popup_size, 0, cg_popup, TRUE);
	}

	return true;
}

