# AI_HW
the homework for AI class

這是一項課程作業，讓AI下棋

遊戲方法 
在 8x8 棋盤上，雙方各有五個棋子
ABefg: AB可四方向移動1~2格,efg為1格
XYuvw: XY可四方向移動1~2格,uvw為1格
該次移動落於對方棋子上,即可吃掉對方


遊戲規則：
開局：在 8x8 棋盤上，設定起始棋局，
         棋局可隨機產生，裁判揭開棋局後，雙方
         自行以鍵盤輸入/滑鼠點選/或讀入文字檔
         等方式輸入各自作業的程式中。
輸入：(1) 由 AB 方先移動，在輸入開局狀態後
            即視同第一次輸入，應開始運算並輸出回應
         (2) 之後雙方輪流輸入對方棋步，並在時間內輸出回應
         (3) 回應具可讀性即可，可用純文字座標(e.g. A(1,4)-(1,5))、
             文字碼繪圖(如右上圖示)、或圖形界面呈現
順序： 由 AB 方先移動，雙方每次必須輪流移動一子
動作： 可在無阻擋狀態下移入空格，或吃掉對方在目的地上的棋子
時間： 每次輸入之後的回應時間必須小於60秒(服從裁判判決)，
          但每局有3次機會可延長該次回應最多至120秒


在撰寫程式的時候，tree為棋盤狀態，gameTree為展開。
gameTree.minmax()為非遞迴函式，下一步預計將其修改成遞迴結構?