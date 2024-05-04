const float  start_game_opt_x = 300, start_game_opt_y = 50;//menu index '1'
const float  select_car_opt_x = 415, select_car_opt_y = 50;//menu index '2'.
const float  select_music_opt_x = 530, select_music_opt_y = 50;
const float  high_score_opt_x = 645, high_score_opt_y = 50;
const float  how_to_play_opt_x = 760, how_to_play_opt_y = 50;
const float  about_opt_x = 875, about_opt_y = 50;
const float  main_menu_r = 40, player_name_x = 515, player_name_y = 390, player_name_dx = 400, player_name_dy = 80;
const float  exit_opt_x = 990, exit_opt_y = 50, go_button_x = 615, go_button_y = 300, go_button_dx = 200, go_button_dy = 60;
const float  go_back_x = 60, go_back_y = 40, go_back_dx = 120, go_back_dy = 40;
const float  play_music_x = 575, play_music_y = 500, music_buttons_dx = 250, music_buttons_dy = 50;
const float  music_choice[5][2] = {{play_music_x-40-music_buttons_dx, play_music_y-50-music_buttons_dy},{play_music_x, play_music_y-50-music_buttons_dy}, {play_music_x+40+music_buttons_dx,play_music_y-50-music_buttons_dy},{play_music_x-20-music_buttons_dx/2, play_music_y-100-2*music_buttons_dy},{play_music_x+20+music_buttons_dx/2, play_music_y-100-2*music_buttons_dy}};
char view_choose = 'n', quit_game_ask = 'n';
/*

there is a char menu_state[2] which keeps record of in which menu and menu items we are at a time. according to this we'll display 
needed menu items or the gameplay etc.

if menu_state[0] = 0-->it's the opening menu.
if menu_stat[0] = 1 ---> it's start game

...

...

the second element of the array will determine which options from a menu is choosen.

*/