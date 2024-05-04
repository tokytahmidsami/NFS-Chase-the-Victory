#include "world.h"
//iGraphics is in the world.h header

short int screen_height = 860, screen_width = 1430, sound_counter = 0, car_num = 4, menu_state = 0, chosen_music = 0, base_score = 1500, 
		  music_winodw_button = -1, player_name_char_index = 0, player_rank = 1, chosen_car = 0, image_to_show = 3, count = 0;
char digits[10][22] = {"images\\digits\\0.bmp", "images\\digits\\1.bmp", "images\\digits\\2.bmp", "images\\digits\\3.bmp", "images\\digits\\4.bmp", "images\\digits\\5.bmp", "images\\digits\\6.bmp", "images\\digits\\7.bmp", "images\\digits\\8.bmp", "images\\digits\\9.bmp"},
	 musics[5][20] = {"musics\\music1.wav", "musics\\music2.wav", "musics\\music3.wav", "musics\\music4.wav", "musics\\music5.wav"},
	 car_images[2][8][40]= {{"images\\cars\\car_1\\car_0_3.bmp", "images\\cars\\car_1\\car_0_2.bmp", "images\\cars\\car_1\\car_0_1.bmp", "images\\cars\\car_1\\car_0.bmp", "images\\cars\\car_1\\car_0_-1.bmp", "images\\cars\\car_1\\car_0_-2.bmp", "images\\cars\\car_1\\car_0_-3.bmp", "images\\cars\\car_1\\display_car.bmp"}, 
							{"images\\cars\\car_2\\car_0_3.bmp", "images\\cars\\car_2\\car_0_2.bmp", "images\\cars\\car_2\\car_0_1.bmp", "images\\cars\\car_2\\car_0.bmp", "images\\cars\\car_2\\car_0_-1.bmp", "images\\cars\\car_2\\car_0_-2.bmp", "images\\cars\\car_2\\car_0_-3.bmp", "images\\cars\\car_2\\display_car.bmp"}},
	 play_music = 'y', score_loaded_from_file = 'n', player_score_loaded = 'n', finish = 'y', take_player_name = 'y', _key = 0, game_finished = 'n', game_loaded = 'n';

player players[6];
FILE *f, *c; 
int player_score = 0;
float car_x = 300, car_y = 20;
car cars[10], player_car;
finish_line f_line;
point p;

void iDraw(){
	iClear();

	if(menu_state == 1){//gameplay window

		if(f_line.finish_line_z < depth) player_rank = 1;
		//main game............................
		if(game_loaded == 'y'){

			count++; //if(curr_health < max_health) curr_health += 0.00005/diff_fact;
			if(count >= 120 || count < 1) count = 1;
			draw_world(_key);
			if(quit_game_ask == 'n'){
				drive_player_car(&player_car, _key);
				for(int i=0; i < (int)(car_num*diff_fact); i++){
					count += i+1;
					drive_car(&cars[i], &player_car, &f_line, count);
				}
			}
			sort_cars(cars, (int)(car_num*diff_fact));
			for(int i=0; i< (int)(car_num*diff_fact); i++){
				draw_car(cars[i]);
				if(cars[i].car_z < depth && f_line.finish_line_z <= depth) player_rank++;
			}
			//drive and draws
			drive_n_draw_finish_line(&f_line, _key);
			drive_n_draw_point_n_barrier(&p, &player_car, &f_line, count);
			drive_n_draw_boost(&p, &player_car, &f_line, count);
			//draw player car
			image_to_show = (player_car.car_x < 143)? 0: (player_car.car_x < 286)? 1: (player_car.car_x < 414)? 2: (player_car.car_x < 572)? 3: (player_car.car_x < 730)? 4: (player_car.car_x < 858)? 5: 6;
			iShowBMP2(player_car.car_x, player_car.car_y, car_images[chosen_car][image_to_show], 0);

			//showing player rank
			char rank[4]; sprintf(rank, "%d", player_rank);
			iSetColor(230, 230, 230);
			iFilledRectangle(50, 650, 155, 50);
			iSetColor(0, 0, 10);
			iRectangle(50, 650, 155, 50);
			iText(60, 670, "Your Rank: ", GLUT_BITMAP_TIMES_ROMAN_24),
			iText(180, 670, rank, GLUT_BITMAP_TIMES_ROMAN_24);
			//health bar
			draw_health_bar();
			//progress bar
			draw_progress_bar(&f_line);
			//draw speedometer
			draw_speedometer();
			//point bar
			draw_point_bar();
			//invincibility bar
			draw_invincibility_bar();
			//ending game
			if(f_line.finish_line_z >= depth || curr_health <= 0){
				player_score = (base_score / player_rank + point_collected*score_per_point + hit_got * loss_per_hit) * (int)pow(diff_fact, diff_fact);
				game_finished = 'y';
				sprintf(players[5].score, "%d", player_score);
				menu_state = 8; //go to score
			}
			if(_key == '0') quit_game_ask = (quit_game_ask == 'n')? 'y': 'n';
			if(quit_game_ask == 'y'){
				iShowBMP2(570, 300, "images\\quit.bmp", 0);
				if(_key == 13) menu_state = 0;
			}
		}
		else{
			for(int i=0; i < 5*diff_fact; i++){
				cars[i].max = 12-0.2*i, cars[i].max_2 = cars[i].max * diff_fact, cars[i].acceleration *= diff_fact;
				cars[i].color_factor = i, cars[i].car_chosen = i % 2;
			}
			f_line.finish_line_z = f_line_z/diff_fact, road_strip_z = 2*f_line.finish_line_z;
			p.barrier_dz = 800/sqrt(diff_fact), p.coin_freq = 4*sqrt(diff_fact);
			//if(_key == 13) game_loaded = 'y';
			game_loaded = 'y';
		}
	}
	//finish_game.............
	else if(menu_state == 8){//score showing
		if(player_score_loaded == 'n') player_score_loaded = 'y';
		if(curr_health <= 0){
			iSetColor(150, 0, 0);
			iFilledRectangle(0, 0, 1430, 860);
			iSetColor(256, 256, 256);
			iText(690, 490, "Game ended !", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(650, 350, "You Died Before Victory!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else{
			sort_player(players, 6);
			iShowBMP(0, 0, "images\\menu_bgs\\show_score.bmp");
			char score[10];
			sprintf(score, "%d", player_score);
			for(int i = 0; score[i] != '\0'; i++) iShowBMP2(725+i*57, 430, digits[score[i]-'0'], 0);
			iShowBMP2(0, 0, "images\\guides\\guide_2.bmp", 0), iShowBMP2(980, 0, "images\\guides\\guide_1.bmp", 0);
			iSetColor(255, 250, 250); 
			iText(50, 600, "Alright, armchair driver, spill the beans!", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(85, 565, "How epic was my victory lap?", GLUT_BITMAP_TIMES_ROMAN_24);
			//player_score = 1900;
			if(player_score >= 1800/sqrt(diff_fact)) iText(1100, 580, "In a word...LEGENDARY!", GLUT_BITMAP_TIMES_ROMAN_24);
			else if(player_score >= 1400/sqrt(diff_fact)) iText(1120, 580, "Sooo... Impressive!", GLUT_BITMAP_TIMES_ROMAN_24);
			else if(player_score >= 1000/sqrt(diff_fact)) iText(1090, 580, "Not everyone can do this!", GLUT_BITMAP_TIMES_ROMAN_24);
			else if(player_score >= 600/sqrt(diff_fact)) iText(1110, 580, "Frankly, Average...", GLUT_BITMAP_TIMES_ROMAN_24);
			else if(player_score >= 400/sqrt(diff_fact)) iText(1100, 580, "A little disappointed, Pal!", GLUT_BITMAP_TIMES_ROMAN_24);
			else if(player_score >= 300/sqrt(diff_fact)) iText(1130, 580, "In a word... BAD!", GLUT_BITMAP_TIMES_ROMAN_24);
			else iText(1100, 580, "Let's learn how to race", GLUT_BITMAP_TIMES_ROMAN_24);
			f = fopen("players.txt", "w");
			for(int i=0; i<5; i++) fprintf(f, players[i].name), fprintf(f, " "), fprintf(f, players[i].score), fprintf(f, "\n");
		}
		if(_key == '0' || _key == 13) menu_state = 0;// go to home
	}
	else if(menu_state == 9){//player name taking
		iShowBMP(0, 0, "images\\menu_bgs\\player_name.bmp");
		if(_key && _key != 32 && _key != 8 && _key != 13){
			players[5].name[player_name_char_index] = _key;
			player_name_char_index++;
		}
		else if(_key == 8 && player_name_char_index>0) player_name_char_index--, players[5].name[player_name_char_index] = '\0', _key=0;
		else if(_key == 13) menu_state = 1;//go to game
		iSetColor(256, 256, 205);
		iText(player_name_x+20, player_name_y+35, players[5].name, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255*(diff_fact-1.0), 255*(2.0-diff_fact), 0);
		iFilledRectangle(player_name_x+3, player_name_y - 2*player_name_dy+1, player_name_dx * (diff_fact - 0.99), 17);
		iSetColor(2, 2, 50), iFilledCircle(player_name_x + player_name_dx * (diff_fact - 0.99), player_name_y - 2*player_name_dy+10, 10);
		iSetColor(255, 255, 255), iCircle(player_name_x + player_name_dx * (diff_fact - 0.99), player_name_y - 2*player_name_dy+10, 10);
		char level[4]; sprintf(level, "%0.2lf", diff_fact);
		iSetColor(255, 255, 255); iText(player_name_x+player_name_dx/2 - 20, player_name_y - 2*player_name_dy+4, level, GLUT_BITMAP_HELVETICA_18);
	}
	else if(menu_state == 0){//openning window

		//resetting world..............................................................................
		player_score_loaded = 'n', player_name_char_index = 0, curr_health = max_health, invincible = 0;
		cars[0].car_x = 200, cars[1].car_x = 1100, cars[2].car_x = 200, cars[3].car_x = 1100, cars[4].car_x = 200;
		cars[5].car_x = 200, cars[6].car_x = 1100, cars[7].car_x = 200, cars[8].car_x = 1100, cars[9].car_x = 200;
		cars[0].car_z = depth, cars[1].car_z = depth, cars[2].car_z = depth - 100, cars[3].car_z = depth - 100, cars[4].car_z = depth + 100;
		cars[5].car_z = depth+200, cars[6].car_z = depth+100, cars[7].car_z = depth - 200, cars[8].car_z = depth + 200, cars[9].car_z = depth + 300;
		cars[0].velocity = cars[1].velocity = cars[2].velocity = cars[3].velocity = cars[4].velocity = 0;
		cars[5].velocity = cars[6].velocity = cars[7].velocity = cars[8].velocity = cars[9].velocity = 0;
		player_car.car_x = 700, game_loaded = 'n', quit_game_ask = 'n';
		cars[0].health = cars[1].health = cars[2].health = cars[3].health = cars[4].health = 1.00;
		cars[5].health = cars[6].health = cars[7].health = cars[8].health = cars[9].health = 1.00;
		road_strip_z = 2*f_line.finish_line_z, player_car_v = 0;
		p.z = 0, p.boost_z = -10, point_collected = 0, hit_got = 0, player_score = 0, diff_fact = 1.5;
		//.......................................................................................

		memset(players[5].name, '\0', 20);
		if(score_loaded_from_file == 'n'){
			f = fopen("players.txt", "r");
			for(int i=0; i<5; i++){
				fscanf(f, "%s", players[i].name);
				fscanf(f, "%s", players[i].score);
			}
			score_loaded_from_file = 'y';
			sort_player(players, 5);
		}
		iShowBMP(0,0,"images\\menu_bgs\\menu_bg.bmp");
	}

	else if(menu_state == 2){//select_car menu window 
		if(_key == '.') chosen_car = 1; else if(_key == ',') chosen_car = 0;
		iShowBMP(0,0, "images\\menu_bgs\\select_car.bmp");
		if(chosen_car == 0) iShowBMP2(500, 280, car_images[chosen_car][7], 0);
		else iShowBMP2(500, 270, car_images[chosen_car][7], 0);
		iShowBMP2(930, 0, "images\\guides\\guide_2.bmp", 0);
		iSetColor(0, 0, 0), iText(100, 620, "Day View", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255), iText(90, 720, "Night View", GLUT_BITMAP_TIMES_ROMAN_24);
		if(view == 'n') iSetColor(255, 255, 255), iFilledCircle(210, 725, 5);
		else if(view == 'd') iSetColor(0, 0, 0), iFilledCircle(210, 625, 5);
		iSetColor(255, 255, 255);
		if(car_view_mode == 'i') iFilledCircle(1000, 720, 5); else if(car_view_mode == 'd') iFilledCircle(1250, 720, 5);
		iShowBMP2(1200, 720, "images\\cars\\opp_car_1.bmp", 255), iShowBMP2(1000, 740, "images\\cars\\opp_car_2.bmp", 0), iShowBMP2(900, 740, "images\\cars\\opp_car_3.bmp", 0);
	}

	else if(menu_state == 3){//select_music window

		iShowBMP(0, 0, "images\\menu_bgs\\select_music.bmp");
		//play music: on/ off button
		if(music_winodw_button == 5){
			iSetColor(255, 255, 255);
			iRectangle(play_music_x, play_music_y, music_buttons_dx, music_buttons_dy);
		}

		iSetColor(256, 220, 256);
		if(play_music == 'y') iText(play_music_x+50, play_music_y+17, "Play Music: ON", GLUT_BITMAP_TIMES_ROMAN_24);
		else iText(play_music_x+50, play_music_y+17, "Play Music: OFF", GLUT_BITMAP_TIMES_ROMAN_24);
		//...................................................

		//highlighting music buttons
		if(music_winodw_button>=0 && music_winodw_button<=4){
			iSetColor(255, 255, 255);
			iRectangle(music_choice[music_winodw_button][0], music_choice[music_winodw_button][1], music_buttons_dx, music_buttons_dy);
		}
		//...................................................
	}

	else if(menu_state == 4){//high score showing window

		iShowBMP(0, 0, "images\\menu_bgs\\high_score.bmp");
		//showing score......................................
		iSetColor(256, 256, 205);
		int x = 300, y = 630, reduce = 110;
		for(int i=0; i<5; i++){
			iText(x, y-reduce*i, players[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(x+800, y-reduce*i, players[i].score, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		//...................................................
	}

	else if(menu_state == 5){// guide window
		iShowBMP(0, 0, "images\\menu_bgs\\how_to_play.bmp");
		iShowBMP2(930, 0, "images\\guides\\guide_3.bmp", 0);
	}

	else if(menu_state == 6){//about window
		iShowBMP(0, 0, "images\\menu_bgs\\about_us.bmp");
		iShowBMP2(1050, 0, "images\\guides\\guide_4.bmp", 0);
	}

	if(_key == GLUT_KEY_F10){
		if(play_music=='y') play_music='n', PlaySound(0, 0, 0);
		else play_music = 'y', PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
	}

	_key = 0;
}

void iMouseMove(int mx, int my) {
	printf("%d\n", count);
}

void iMouse(int button, int state, int mx, int my) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(menu_state == 0){//openning menu
			if(start_game_opt_x-main_menu_r<=mx && start_game_opt_x+main_menu_r>=mx && start_game_opt_y-main_menu_r<=my && my<=start_game_opt_y+main_menu_r){
				menu_state = 9;
			}
			else if(select_car_opt_x-main_menu_r<=mx && select_car_opt_x+main_menu_r>=mx && select_car_opt_y-main_menu_r<=my && my<=select_car_opt_y+main_menu_r){
				menu_state = 2;
			}
			else if(select_music_opt_x-main_menu_r<=mx && select_music_opt_x+main_menu_r>=mx && select_music_opt_y-main_menu_r<=my && my<=select_music_opt_y+main_menu_r){
				menu_state = 3;
			}
			else if(high_score_opt_x-main_menu_r<=mx && high_score_opt_x+main_menu_r>=mx && high_score_opt_y-main_menu_r<=my && my<=high_score_opt_y+main_menu_r){
				menu_state = 4;
			}
			else if(how_to_play_opt_x-main_menu_r<=mx && how_to_play_opt_x+main_menu_r>=mx && how_to_play_opt_y-main_menu_r<=my && my<=how_to_play_opt_y+main_menu_r){
				menu_state = 5;
			}
			else if(about_opt_x-main_menu_r<=mx && about_opt_x+main_menu_r>=mx && about_opt_y-main_menu_r<=my && my<=about_opt_y+main_menu_r){
				menu_state = 6;
			}
			else if(exit_opt_x-main_menu_r<=mx && exit_opt_x+main_menu_r>=mx && exit_opt_y-main_menu_r<=my && my<=exit_opt_y+main_menu_r){
				f = fopen("players.txt", "w");
				for(int i=0; i<5; i++) fprintf(f, players[i].name), fprintf(f, " "), fprintf(f, players[i].score), fprintf(f, "\n");
				exit(0);
			}
		}
		else if(menu_state == 1 && quit_game_ask == 'y'){
			//iRectangle(600, 465, 100, 52), iRectangle(732, 465, 100, 52)
			if(465 <= my && my <= 517){
				if(600 <= mx && mx<= 700) menu_state = 0;
				else if(732 <= mx && mx <= 832) quit_game_ask = 'n';
			}
		}
		else if(menu_state>= 4 && menu_state <=7){
			if(go_back_x<=mx && mx<=go_back_x+go_back_dx && go_back_y<= my && my<= go_back_y+go_back_dy){
				menu_state = 0;
			}
		}
		else if(menu_state == 9){//name taking
			if(go_button_x<=mx && mx<=go_button_x+go_button_dx && go_button_y<=my && my<=go_button_y+go_button_dy) menu_state = 1;
			if(go_back_x<=mx && mx<=go_back_x+go_back_dx && go_back_y<= my && my<= go_back_y+go_back_dy) menu_state = 0;
			if(player_name_y - 2*player_name_dy <=my && my <= player_name_y - 2*player_name_dy + 20 && player_name_x <= mx && mx <= player_name_x + player_name_dx) diff_fact = 1.0 + (mx - player_name_x) / player_name_dx;
		}
		else if(menu_state == 2){//car choice
			if(go_back_x<=mx && mx<=go_back_x+go_back_dx && go_back_y<= my && my<= go_back_y+go_back_dy){
				menu_state = 0;
			}
			else if(80<=mx && mx<=345){
				if(320<=my && 385 >= my) chosen_car = 0;
				else if(450 <= my && 515 >= my) chosen_car = 1;
				else if(600 <= my && 650 >= my) view = 'd';
				else if(700 <= my && 750 >= my) view = 'n';
			}
			else if(720 <= my && my <= 820){
				if(900 <= mx && mx <= 1100) car_view_mode = 'i';
				else if(1200 <= mx && mx <= 1300) car_view_mode = 'd';
			}
		}
		else if(menu_state == 3){//music choice
			
			if(go_back_x<=mx && mx<=go_back_x+go_back_dx && go_back_y<= my && my<= go_back_y+go_back_dy){
				menu_state = 0;
			}
			else if(play_music_x<=mx && mx<=play_music_x+music_buttons_dx && play_music_y<=my && my<= play_music_y+music_buttons_dy){
				if (play_music == 'y') play_music = 'n', PlaySound(0, 0, 0), music_winodw_button = 5;
				else play_music = 'y', PlaySound(musics[chosen_music], NULL, SND_LOOP | SND_ASYNC);
			}
			else if(music_choice[0][0]<=mx && mx<=music_choice[0][0]+music_buttons_dx && music_choice[0][1]<=my && my<=music_choice[0][1]+music_buttons_dy){
				chosen_music = 0, music_winodw_button = 0;
				if(play_music == 'y') PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(0, 0, 0);
			}
			else if(music_choice[1][0]<=mx && mx<=music_choice[1][0]+music_buttons_dx && music_choice[1][1]<=my && my<=music_choice[1][1]+music_buttons_dy){
				chosen_music = 1, music_winodw_button = 1;
				if(play_music == 'y') PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(0, 0, 0);
			}
			else if(music_choice[2][0]<=mx && mx<=music_choice[2][0]+music_buttons_dx && music_choice[2][1]<=my && my<=music_choice[2][1]+music_buttons_dy){
				chosen_music = 2, music_winodw_button = 2;
				if(play_music == 'y') PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(0, 0, 0);
			}
			else if(music_choice[3][0]<=mx && mx<=music_choice[3][0]+music_buttons_dx && music_choice[3][1]<=my && my<=music_choice[3][1]+music_buttons_dy){
				chosen_music = 3, music_winodw_button = 3;
				if(play_music == 'y') PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(0, 0, 0);
			}
			else if(music_choice[4][0]<=mx && mx<=music_choice[4][0]+music_buttons_dx && music_choice[4][1]<=my && my<=music_choice[4][1]+music_buttons_dy){
				chosen_music = 4, music_winodw_button = 4;
				if(play_music == 'y') PlaySound(musics[chosen_music], NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(0, 0, 0);
			}
			else music_winodw_button = -1;
		}
	}
}

void iKeyboard(unsigned char key) {
	_key = key;
	if(_key == '0' && menu_state != 1) menu_state = 0;
	// if(_key == 'q') player_car.car_x -= 10;
	// else if(_key == 'e') player_car.car_x += 10;
}

void iSpecialKeyboard(unsigned char key) {
	_key = key;
}

int main() {
	// iSetTimer(1, timer_drive_car);
	// iSetTimer(1, timer_drive_road);
	PlaySound(musics[chosen_music], NULL, SND_LOOP | SND_ASYNC);
	iInitialize(screen_width, screen_height, "Need for Speed: Chase the Victory...");
	return 0;
}





// void timer_drive_car(){
// 	if(quit_game_ask == 'n'){
// 		drive_player_car(&player_car, _key);
// 		for(int i=0; i<car_num*diff_fact; i++){
// 			count += i+1;
// 			drive_car(&cars[i], &player_car, &f_line, count);
// 		}
// 	}
// }

// void timer_drive_road(){
// 	drive_n_draw_road_strip(_key);
// }
