#include "DxLib.h"
#include <string>
#include <deque>
#include "Console.h"
#include "Sound.h"
#include "Pad.h"

static const int KEYCODES[] =
{
	D_DIK_A, D_DIK_B, D_DIK_C, D_DIK_D, D_DIK_E,
	D_DIK_F, D_DIK_G, D_DIK_H, D_DIK_I, D_DIK_J,
	D_DIK_K, D_DIK_L, D_DIK_M, D_DIK_N, D_DIK_O,
	D_DIK_P, D_DIK_Q, D_DIK_R, D_DIK_S, D_DIK_T,
	D_DIK_U, D_DIK_V, D_DIK_W, D_DIK_X, D_DIK_Y,
	D_DIK_Z
};

static const int KEYNUM[] =
{
	D_DIK_0, D_DIK_1, D_DIK_2, D_DIK_3, D_DIK_4,
	D_DIK_5, D_DIK_6, D_DIK_7, D_DIK_8, D_DIK_9
};

static const char NUM_SYMBOLS[] = " !\"#$%&'()";

static const int NUMKEY_NUM[] =
{
	KEY_INPUT_NUMPAD0, KEY_INPUT_NUMPAD1, KEY_INPUT_NUMPAD2,
	KEY_INPUT_NUMPAD3, KEY_INPUT_NUMPAD4, KEY_INPUT_NUMPAD5,
	KEY_INPUT_NUMPAD6, KEY_INPUT_NUMPAD7, KEY_INPUT_NUMPAD8,
	KEY_INPUT_NUMPAD9,
};

struct Console
{
	Sound *sound;
	int is_input;
	int x;
	int y;
	int back_count;
	int signal;
	std::string d_bag; ///< カーソルより前の入力中の文字列。
	std::string after_cursor; ///< カーソルより後の入力中の文字列。反転されて入っている。
	std::deque<std::string> log;
	int enter_time_count;
	int enter_pict;
};

// 初期化をする
Console *Console_Initialize(Sound *sound)
{
	Console *self;
	self = new Console();
	self->sound = sound;
	self->is_input = 1;
	self->x = 0;
	self->y = 420;
	self->signal = 0;
	self->back_count = 0;
	self->enter_time_count = 0;
	self->enter_pict = LoadGraph("meta/enterkey.png");
	return self;
}

int Console_is_input(Console *self)
{
	return self->is_input % 2;
}

/** srcの最後の文字を削ってdstの最後にくっつける。 */
static void reverse_push(std::string &src, std::string &dst)
{
	if (src.empty()) { return; }
	dst += src.back();
	src.erase(src.end() - 1);
}

static void reverse_concat(std::string &src, std::string &dst)
{
	if (src.empty()) { return; }
	dst.append(src.rbegin(), src.rend());
	src.erase();
}

//右キーでの動作
static void cursor_to_right(Console *self)
{
	reverse_push(self->after_cursor, self->d_bag);
}

//左キーでの動作
static void cursor_to_left(Console *self)
{
	reverse_push(self->d_bag, self->after_cursor);
}

//endキーでの動作
static void cursor_to_end(Console *self)
{
	reverse_concat(self->after_cursor, self->d_bag);
}

//homeキーでの動作
static void cursor_to_home(Console *self)
{
	reverse_concat(self->d_bag, self->after_cursor);
}

const char *console_d_bag(Console *self)
{
	if (self->d_bag.empty() && self->after_cursor.empty())
	{
		return NULL;
	}
	else
	{
		cursor_to_end(self);
		return self->d_bag.c_str();
	}
}

void console_shift_log(Console *self)
{
	cursor_to_end(self);
	self->log.push_back(self->d_bag);
	self->d_bag.erase();
}

static int get_chara()
{
	// シフト押してたらtrue
	const bool shift = Pad_Get(KEY_INPUT_LSHIFT) > 0 || Pad_Get(KEY_INPUT_RSHIFT) > 0;

	// アルファベット入力
	for (int i = 0; i < 26; i++)
	{
		if (Pad_Get(KEYCODES[i]) == 1) { return (shift ? 'A' : 'a') + i; }
	}

	//数値入力があった場合
	for (int i = 0; i < 10; i++)
	{
		if (Pad_Get(KEYNUM[i]) == 1 || Pad_Get(NUMKEY_NUM[i]) == 1) { return shift ? NUM_SYMBOLS[i] : '0' + i; }
	}

	// リターンキーを押した時の処理はここではなくScriptにある

	//スペース入力があった場合
	if (Pad_Get(KEY_INPUT_SPACE) == 1) { return ' '; }
	//バックスペース入力があった場合
	if (Pad_Get(KEY_INPUT_BACK) == 1) { return -2; }
	//上矢印キー入力があった場合
	if (Pad_Get(KEY_INPUT_UP) == 1) { return -3; }
	//下矢印キー入力があった場合
	if (Pad_Get(KEY_INPUT_DOWN) == 1) { return -4; }

	//Deleteキー
	if (Pad_Get(KEY_INPUT_DELETE) == 1) { return -5; }

	//左矢印キー入力があった場合
	if (Pad_Get(KEY_INPUT_LEFT) == 1) { return -6; }
	//右矢印入力があった場合
	if (Pad_Get(KEY_INPUT_RIGHT) == 1) { return -7; }
	//Home
	if (Pad_Get(KEY_INPUT_HOME) == 1) { return -8; }
	//End
	if (Pad_Get(KEY_INPUT_END) == 1) { return -9; }

	if (Pad_Get(KEY_INPUT_RETURN) == 1) { return -10; }

	// 記号類 (106)
	if (Pad_Get(KEY_INPUT_MINUS) == 1) { return shift ? '=' : '-'; }
	if (Pad_Get(KEY_INPUT_PREVTRACK) == 1) { return shift ? '~' : '^'; }
	if (Pad_Get(KEY_INPUT_YEN) == 1) { return shift ? '|' : '\\'; }

	if (Pad_Get(KEY_INPUT_AT) == 1) { return shift ? '`' : '@'; }
	if (Pad_Get(KEY_INPUT_LBRACKET) == 1) { return shift ? '{' : '['; }

	if (Pad_Get(KEY_INPUT_SEMICOLON) == 1) { return shift ? '+' : ';'; }
	if (Pad_Get(KEY_INPUT_COLON) == 1) { return shift ? '*' : ':'; }
	if (Pad_Get(KEY_INPUT_RBRACKET) == 1) { return shift ? ' }' : ']'; }

	if (Pad_Get(KEY_INPUT_COMMA) == 1) { return shift ? '<' : ','; }
	if (Pad_Get(KEY_INPUT_PERIOD) == 1) { return shift ? '>' : '.'; }
	if (Pad_Get(KEY_INPUT_SLASH) == 1) { return shift ? '?' : '/'; }
	if (Pad_Get(KEY_INPUT_BACKSLASH) == 1) { return '_'; } // my preference

	if (Pad_Get(KEY_INPUT_MULTIPLY) == 1) { return '*'; }
	if (Pad_Get(KEY_INPUT_DIVIDE) == 1) { return '/'; }
	if (Pad_Get(KEY_INPUT_ADD) == 1) { return '+'; }
	if (Pad_Get(KEY_INPUT_SUBTRACT) == 1) { return '-'; }
	if (Pad_Get(KEY_INPUT_DECIMAL) == 1) { return '.'; }

	//入力がなかった場合
	return -1;
}

// カーソル移動の処理。キー入力が反応するキーでなかったらfalse。反応したらtrueを返す
static bool move_cursor(Console *self, int input)
{
	if (input == -6) // 左矢印
	{
		cursor_to_left(self);
	}
	else if (input == -7) // 右矢印
	{
		cursor_to_right(self);
	}
	else if (input == -8) // Home
	{
		cursor_to_home(self);
	}
	else if (input == -9) // End
	{
		cursor_to_end(self);
	}
	else
	{
		return false;
	}

	return true;
}

//コンソールの開閉
void open_and_shut(Console *self)
{
	if (Pad_Get(KEY_INPUT_RETURN) == -1 && self->is_input % 2 == 1)
	{
		if (self->enter_time_count < 15)
		{
			self->is_input++;
		}
		self->enter_time_count = 0;
	}
	else if (Pad_Get(KEY_INPUT_RETURN) == -1 || Pad_Get(KEY_INPUT_ESCAPE) == -1)
	{
		self->is_input++;
	}

	self->enter_time_count++;
}


// 動きを計算する
void Console_Update(Console *self)
{
	//入力モード時
	if (self->is_input % 2 == 1)
	{
		int bag = get_chara();

		if (bag == -1)
		{
			//入力がない場合
		}
		else
		{
			Sound_type(self->sound, 0);

			if (bag == -2)
			{
				//バックスペース入力があった場合
				//最後の文字を消去
				if (!self->d_bag.empty()) {self->d_bag.erase(self->d_bag.size() - 1);}
			}
			else if (bag == -3)
			{
				//上キー入力があった場合
				int in = self->log.size() - 1 - self->back_count;
				if (self->log.size() > self->back_count)
				{
					self->after_cursor.erase();
					self->d_bag.assign(self->log[in]);
					if (in > 0) {self->back_count++;}
				}

			}
			else if (bag == -4)
			{
				//下キー入力があった場合
				int in = self->log.size() - 1 - self->back_count;
				if (in > -1)
				{
					self->after_cursor.erase();
					self->d_bag.assign(self->log[in]);
					if (self->back_count > 0) {self->back_count--;}
				}
			}
			else if (bag == -5)
			{
				// Deleteキー入力があった場合
				// カーソル直後の文字を消去
				if (!self->after_cursor.empty()) {self->after_cursor.erase(self->after_cursor.size() - 1);}
			}
			else if (bag == -10)
			{
				Sound_type(self->sound, 1);
			}
			else if (!move_cursor(self, bag))
			{
				//文字・数値入力があった場合追加
				self->d_bag += (char) bag;
			}
			self->signal++;
		}
	}
	//入力モード以外
	else
	{
		self->back_count = 0;
	}

	open_and_shut(self);
}

static void mark_enter(Console *self)
{
	int x = 300 + 288;
	int y = 300 + 128;
	int w = 8;
	int h = 16;

	y += Pad_Get(KEY_INPUT_RETURN) > 0 ? 2 : 0;
	y += Console_is_input(self) ? -64 : 16;

	DrawGraph(x, y, self->enter_pict, TRUE);

	x += 15;

	if (Console_is_input(self))
	{
		y += 47;
		DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), TRUE);
		DrawTriangle(x - w / 2, y + h, x + w * 3 / 2, y + h, x + w / 2, y + h * 3 / 2, GetColor(255, 255, 255), TRUE);
	}
	else
	{
		y -= h;
		DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), TRUE);
		DrawTriangle(x - w / 2, y, x + w * 3 / 2, y, x + w / 2, y - h / 2, GetColor(255, 255, 255), TRUE);
	}
}


// 描画する
void Console_Draw(Console *self)
{
	ChangeFont( "ＭＳ ゴシック" );
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180) ;
	SetFontSize(16) ;

	int plus;
	if (self->is_input % 2 == 1) {plus = -80;}
	else {plus = 0;}

	DrawBox(0, 465 +  plus, 640 , 470 + plus, GetColor(255 , 255 , 255), TRUE) ;
	DrawBox(0, 470 +  plus, 640 , 480, GetColor(0 , 0 , 200), TRUE) ;
	mark_enter(self);

	if (self->is_input % 2 == 1)
	{
		int cursor_x = self->x + self->d_bag.size() * 9;
		int padd_y = -5;
		int padd_x = +10;

		for (int i = 0; i < self->log.size() ; i++)
		{
			DrawFormatString(self->x + padd_x , 433 - i * 15, GetColor(255, 255, 0), "%s", self->log[self->log.size() - 1 - i].c_str());  //ログを描画する
			if (i == 3) {break;}
		}
		if (self->signal % 100 < 90)
		{
			//カーソル位置
			DrawFormatString(cursor_x + padd_x, 463 + padd_y, GetColor(0, 255, 0), "%s", "■");
		}

		// 現在の文字を描画する
		DrawFormatString(self->x + padd_x, 463 + padd_y, GetColor(0, 255, 0), "%s", self->d_bag.c_str());

		// カーソルのあとの文字を描画する
		for (int i = 0; i < self->after_cursor.size(); i++)
		{
			char c = self->after_cursor[self->after_cursor.size() - i - 1];
			DrawFormatString(cursor_x + 9 + padd_x * (i + 2), 463 + padd_y, GetColor(0, 255, 0), "%c", c);
		}
	}
}

// 終了処理をする
void Console_Finalize(Console *self)
{
	DeleteGraph(self->enter_pict);
	delete self;
}
