#include<stdio.h>
#include"common.h"
#include"daihinmin.h"
#include"select_cards.h"

void select_change_cards(int out_cards[8][15],int my_cards[8][15],int num_of_change){
 int count=0;
  int one_card[8][15];
  
  clear_table(out_cards);
  while(count<num_of_change){
    search_low_card(one_card,my_cards,0);
    diff_cards(my_cards,one_card);
    or_cards(out_cards,one_card);
    count++;
  }
}

void select_submit_cards(int out_cards[8][15],int my_cards[8][15], state *field_status){
  int select_cards[8][15];
 
  clear_table(select_cards);

  if(field_status->is_rev==0){
    if(field_status->is_no_card==1){                //????????????????????
      select_cards_free(select_cards, my_cards, field_status);    //??????????????
    }else{
      select_cards_restrict(select_cards,my_cards, field_status);    //??????????????
    }
  }else{
    if(field_status->is_no_card==1){                //????????????????????
      select_cards_free_rev(select_cards, my_cards, field_status); //??????????????
    }else{
      select_cards_restrict_rev(select_cards, my_cards, field_status); //??????????????
    }
  }

  copy_table(out_cards, select_cards);
}

void select_cards_free(int select_cards[8][15], int my_cards[8][15], state *field_status){
  //search_low_card(select_cards,my_cards,0);?

  int info_table[8][15];

  make_info_table(info_table,my_cards);

  if(count_cards(select_cards)==0)
    search_low_sequence(select_cards, info_table);

  if(count_cards(select_cards)==0)
    search_low_pair(select_cards, info_table, my_cards);

  if(count_cards(select_cards)==0)
    search_low_card(select_cards, my_cards, 0);
}

void select_cards_restrict(int select_cards[8][15], int my_cards[8][15], state *field_status){
  int tmp_cards[8][15];

  int info_table[8][15];
 
  copy_table(tmp_cards, my_cards); 

  if(field_status->is_sequence==1){ // 階段
    if(field_status->is_lock==1){ // しばり~２度同じ記号ならば以降も同じ記号
      remove_suit(tmp_cards, field_status->suit, 1);//suit以外の記号を持っていないものとする
      remove_low_card(tmp_cards, field_status->order, 0); 
      make_info_table(info_table,my_cards);
      search_low_sequence_restrict(select_cards, info_table, field_status->quantity); 
    }else{ // しばりなし
      remove_low_card(tmp_cards, field_status->order, 0); //手持ちで場に出ているカードよりも弱いカードを持っていないものとする
      make_info_table(info_table,my_cards);
      search_low_sequence_restrict(select_cards, info_table, field_status->quantity); 
    }

  }else if(field_status->quantity > 1){ // 場に二枚以上あるとき
    if(field_status->is_lock==1){ // しばり
      remove_suit(tmp_cards, field_status->suit, 1);//suit以外の記号を持っていないものとする
      make_info_table(info_table,my_cards);
      remove_low_card(tmp_cards, field_status->order, 0); 
      search_low_pair_restrict(select_cards, info_table, tmp_cards,field_status->quantity); 
    }else{ // しばりなし
      remove_low_card(tmp_cards, field_status->order, 0); //手持ちで場に出ているカードよりも弱いカードを持っていないものとする
      make_info_table(info_table,my_cards);
      search_low_pair_restrict(select_cards, info_table, tmp_cards,field_status->quantity); 
    }

  }else{ // ??????????????
    if(field_status->is_lock==1){ // ????????????????
      remove_suit(tmp_cards, field_status->suit, 1);
      remove_low_card(tmp_cards, field_status->order, 0); 
      search_low_card(select_cards,tmp_cards,1); 
    }else{ // ??????????????????
      remove_low_card(tmp_cards, field_status->order, 0); 
      search_low_card(select_cards,tmp_cards,1); 
    }
  }
}

void select_cards_free_rev(int select_cards[8][15], int my_cards[8][15], state *field_status){
}

void select_cards_restrict_rev(int select_cards[8][15], int my_cards[8][15], state *field_status){
}

void operate_my_cards(int my_cards[8][15], state *field_status){
}

void operate_field_cards(int ba_cards[8][15], state *field_status){
}
