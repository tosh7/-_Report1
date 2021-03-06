// heikatsu.c  このプログラムの名前
// ****************************************************
// これは「不完全な」プログラムです．このプログラムの
// ㈰，㈪，㈫の部分に適切な記述を補って，正しく動作す
// るプログラムに変えてから提出して下さい．
// ****************************************************
#include<stdio.h>
#include"pgmlib.h"

int main(void) {
    int h;                     // 変換後のヒストグラムの高さ
    int fmin = 255, fmax = 0;  // 画像の最低階調値・最大階調値
    int x,y;                   // 制御変数
    int g=0;                   // 変換後の初期階調値
    int count;                 // 各階調 g の画素の数
    int f;                     // ㈫で階調についてのforループを
    // 作るときの制御変数
    
    printf("===== ヒストグラム平滑化のプログラム ===\n");
    printf("原画像を読み込みます\n");
    load_image( 0, "" );       // ファイル → 画像No.0 へ読み込み
    copy_image( 0, 1 );        // 画像No.0 → 画像No.1 へコピー
    
    // h (＝平滑化後のヒストグラムの高さ）を求める
    h = height[1] * width[1] / 256;
    printf("ヒストグラムの高さ = %d\n",h);
    
    // image[0] の最小階調値 fmin, 最大階調値 fmax を求める
    for(y = 0; y < height[0]; y++) {
        for(x = 0; x < width[0]; x++) {
            int tempNumber = image[0][x][y];
            
            if(tempNumber < fmin){
                fmin = tempNumber;
            }
            if(tempNumber > fmax) {
                fmax = tempNumber;
            }
        }
    }
    
    printf("原画像の最小階調値＝%d, 最大階調値=%d\n",fmin,fmax);
    
    // 変換する
    // 原画像の最小階調値から最大階調値までを走査しながら，
    // 変換後の画像の階調値を g=0 から順に g=255 まで埋めていく
    // count は，各gでの画素数のカウンタで，count=h になったら，
    // g の値に１を加える
    for(f = fmin; f <= fmax; f++) {
        for(y = 0; y < height[0]; y++) {
            for(x = 0; x < width[0]; x++) {
                if(image[0][x][y] == f){
                    image[1][x][y] = g;
                    count += 1;
                    if(count == h){
                        count = 0;
                        g++;
                    }
                }
            }
        }
    }
    
    printf("ヒストグラム平滑化が終了しました\n");
    
    
    
    printf("処理後の画像を保存します\n");
    save_image( 1, "" );  // 画像No.1 → ファイル
    return 0;
}

