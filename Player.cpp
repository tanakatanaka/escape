#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

// ‰Šú‰»‚ğ‚·‚é
void Player_Initialize( Player_t *Player, int y, int img ){
    Player->Image = img;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
    Player->y     = y;        //yÀ•WŠi”[
}

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player_t *Player ){
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 ){//ã‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        Player->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 ){//‰º‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        Player->y++;
    }
}

// •`‰æ‚·‚é
void Player_Draw( Player_t Player ){
    DrawGraph( 0, Player.y, Player.Image, TRUE );
}

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player_t Player ){
    DeleteGraph( Player.Image );
}
