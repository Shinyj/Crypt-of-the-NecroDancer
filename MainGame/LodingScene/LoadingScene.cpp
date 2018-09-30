#include "stdafx.h"
#include "../../stdafx.h"
#include "LoadingScene.h"
#include "../../GameNode.h"

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::Init()
{
	SOUNDMANAGER->AddSound("zone1_3", "sound/zone1_3.ogg", true, true);
	SOUNDMANAGER->SetBit("zone1_3");
	SOUNDMANAGER->Play("zone1_3", 0.5);

	RECT rcClient = { 0,0,960,540 };
	
	AdjustWindowRect(
		&rcClient,
		WINSTYLE,
		FALSE);

	SetWindowPos(

		hWnd, NULL,
		0, 0,
		(rcClient.right - rcClient.left),
		(rcClient.bottom - rcClient.top),
		SWP_NOZORDER | SWP_NOMOVE);


	_loading = new Loading;
	//_loading->InitForSound("zone1_3", "sound/zone1_3.ogg", true, true);


	_loading->Init();
	
	this->TotalLoading();

	return S_OK;
}

void LoadingScene::Release()
{
	SAFE_DELETE(_loading);
}

void LoadingScene::Update()
{
	_loading->Update();
	
	if (_loading->LoadingDone())
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->Play("zone1_3");
			SOUNDMANAGER->Stop("zone1_3");
			OBJECTMANAGER->Init();
			//SCENEMANAGER->ChangeScene("lobby");
			//lobby levelEdit
			SCENEMANAGER->ChangeScene("lobby");
		}
	}
}

void LoadingScene::Render()
{

	_loading->Render();
}

void LoadingScene::TotalLoading()
{
	/*for (int i = 0; i < 1000; i++)
	{
		_loading->InitForFrameImage("floor_boss", "images/level/floor_boss.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	}*/

	_loading->InitForFrameImage("floor_boss", "images/level/floor_boss.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_npc", "images/level/floor_npc.bmp", TILESIZE * 3, TILESIZE, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_shop", "images/level/floor_shop.bmp", TILESIZE * 3, TILESIZE, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_shop_next", "images/level/floor_shop_next.bmp", TILESIZE, TILESIZE, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_shop_reset", "images/level/floor_shop_reset.bmp", TILESIZE, TILESIZE, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_stairs", "images/level/floor_stairs.bmp", TILESIZE, TILESIZE, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_stairs_locked", "images/level/floor_stairs_locked.bmp", TILESIZE, TILESIZE, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_zone1", "images/level/floor_zone1.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_zone2", "images/level/floor_zone2.bmp", TILESIZE * 3, TILESIZE * 4, 3, 4, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_zone3_cold", "images/level/floor_zone3_cold.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_zone3_hot", "images/level/floor_zone3_hot.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("floor_zone4", "images/level/floor_zone4.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_door_front", "images/level/wall_door_front.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_door_side", "images/level/wall_door_side.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_end", "images/level/wall_end.bmp", TILESIZE * 8, WALLHEIGHT, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_shop_stone", "images/level/wall_shop_stone.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_shop_stone_cracked", "images/level/wall_shop_stone_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_z1_drit", "images/level/wall_zone1_drit.bmp", TILESIZE * 16, WALLHEIGHT, 16, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_z1_stone", "images/level/wall_zone1_stone.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone1_stone_cracked", "images/level/wall_zone1_stone_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_z2", "images/level/wall_zone2.bmp", TILESIZE * 8, WALLHEIGHT, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_z2_stone", "images/level/wall_zone2_stone.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone2_stone_cracked", "images/level/wall_zone2_stone_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_dirt_cold", "images/level/wall_zone3_dirt_cold.bmp", TILESIZE * 8, WALLHEIGHT, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_dirt_hot", "images/level/wall_zone3_dirt_hot.bmp", TILESIZE * 8, WALLHEIGHT, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_stone_cold", "images/level/wall_zone3_stone_cold.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_stone_cold_cracked", "images/level/wall_zone3_stone_cold_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_stone_hot", "images/level/wall_zone3_stone_hot.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone3_stone_hot_cracked", "images/level/wall_zone3_stone_hot_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone4_dirt", "images/level/wall_zone4_dirt.bmp", TILESIZE * 8, WALLHEIGHT, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone4_stone", "images/level/wall_zone4_stone.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("wall_zone4_stone_cracked", "images/level/wall_zone4_stone_cracked.bmp", TILESIZE, WALLHEIGHT, 1, 1, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("wall_torch", "images/level/wall_torch.bmp", 96, 52, 4, 1, true,(RGB(255, 0, 255)));

	_loading->InitForFrameImage("boss_wall", "images/level/boss_wall.bmp", TILESIZE*5, WALLHEIGHT, 5, 1, true, RGB(255, 0, 255));

	///////////////////////// 몬스터 이미지

	_loading->InitForFrameImage("banshee", "images/monster/banshee.bmp", 544 * 2, 156, 16, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("banshee2", "images/monster/banshee2.bmp", 544 * 2, 156, 16, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("bat_black", "images/monster/bat_black.bmp", 192 * 2, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("bat_green", "images/monster/bat_green.bmp", 192 * 2, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("bat_miniboss", "images/monster/bat_miniboss.bmp", 288 * 2, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("miniboss_yellow", "images/monster/bat_miniboss_yellow.bmp", 288 * 2, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("bat_red", "images/monster/bat_red.bmp", 192 * 2, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("dragon_red", "images/monster/dragon_red.bmp", 854 * 2, 204, 14, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("minotaur", "images/monster/minotaur.bmp", 900 * 2, 204, 18, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("minotaur2", "images/monster/minotaur2.bmp", 900 * 2, 196, 18, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("skeleton", "images/monster/skeleton.bmp", 384 * 2, 100, 16, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("skeleton_black", "images/monster/skeleton_black.bmp", 432 * 2, 100, 18, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("mage_black", "images/monster/skeleton_mage_black.bmp", 336 * 2, 100, 14, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("mage_white", "images/monster/skeleton_mage_white.bmp", 336 * 2, 108, 14, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("mage_yellow", "images/monster/skeleton_mage_yellow.bmp", 336 * 2, 108, 14, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("skeleton_yellow", "images/monster/skeleton_yellow.bmp", 432 * 2, 108, 18, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slime_blue", "images/monster/slime_blue.bmp", 416 * 2, 100, 16, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slime_green", "images/monster/slime_green.bmp", 208 * 2, 104, 8, 2, true, RGB(255, 0, 255));


	////////////////////// 아이템 이미지

	_loading->InitForFrameImage("armor_gi", "images/item/armor_gi.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("armor_glass", "images/item/armor_glass.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("armor_chain", "images/item/armor_chain.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("armor_leather", "images/item/armor_leather.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("food_2", "images/item/food_2.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("shovel_basic", "images/item/shovel_basic.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("shovel_titanium", "images/item/shovel_titanium.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("torch_1", "images/item/torch_1.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("torch_2", "images/item/torch_2.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("torch_3", "images/item/torch_3.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_gun", "images/item/weapon_gun.bmp", 100, 144, 2, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_bow", "images/item/weapon_bow.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_broad", "images/item/weapon_broad.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_dagger", "images/item/weapon_dagger.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_flail", "images/item/weapon_flail.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_long", "images/item/weapon_long.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_rapier", "images/item/weapon_rapier.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("weapon_spear", "images/item/weapon_spear.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));

	/////////// 멥 툴에서는 안다루는 아이템

	_loading->InitForFrameImage("bomb", "images/item/bomb.bmp", 240, 96, 5, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin2", "images/item/resource_coin2.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin3", "images/item/resource_coin3.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin4", "images/item/resource_coin4.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin5", "images/item/resource_coin5.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin6", "images/item/resource_coin6.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin7", "images/item/resource_coin7.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin8", "images/item/resource_coin8.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin9", "images/item/resource_coin9.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin10", "images/item/resource_coin10.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("hoard", "images/item/resource_hoard.bmp", 68, 76, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("gold", "images/item/resource_hoard_gold.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("small", "images/item/resource_hoard_gold_small.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));

	////// 아이템 설명 텍스트 이미지

	_loading->InitForImage("hint_0-5defense", "images/option/hint_0-5defense.bmp", 95, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_1defense", "images/option/hint_1defense.bmp", 81, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_1dig", "images/option/hint_1dig.bmp", 85, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_2dig", "images/option/hint_2dig.bmp", 85, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_daggerthrowable", "images/option/hint_daggerthrowable.bmp", 140, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_knockbackattack", "images/option/hint_knockbackattack.bmp", 73, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_longattack", "images/option/hint_longattack.bmp", 56, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_longattackthrowable", "images/option/hint_longattackthrowable.bmp", 164, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_lungefordoubledamage", "images/option/hint_lungefordoubledamage.bmp", 152, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_rangedattack", "images/option/hint_rangedattack.bmp", 92, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_rangedattackneedsloadingpiercing", "images/option/hint_rangedattackneedsloadingpiercing.bmp", 241, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_restore2health", "images/option/hint_restore2health.bmp", 110, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_torch1", "images/option/hint_torch1.bmp", 63, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_torch2", "images/option/hint_torch2.bmp", 63, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_torch3", "images/option/hint_torch3.bmp", 73, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("hint_wideattack", "images/option/hint_wideattack.bmp", 73, 18, true, RGB(255, 0, 255));


	// GUI 관련 이미지
	_loading->InitForFrameImage("diamond", "images/gui/diamond.bmp", 50, 48, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("heart", "images/gui/heart.bmp", 48, 44, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("heart_empty", "images/gui/heart_empty.bmp", 48, 44, 1, 1, true, RGB(255, 0, 255));
	
	_loading->InitForFrameImage("heart_large", "images/gui/heart_large.bmp", 54, 50, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("heart_half_large", "images/gui/heart_half_large.bmp", 54, 50, 1, 1, true, RGB(255, 0, 255));
	
	_loading->InitForFrameImage("heart_half", "images/gui/heart_half.bmp", 48, 44, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("coin", "images/gui/hud_coins.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slot_shovel", "images/gui/hud_slot_1.bmp", 60, 66, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slot_attack", "images/gui/hud_slot_2.bmp", 60, 66, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slot_body", "images/gui/hud_slot_3.bmp", 60, 66, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slot_torch", "images/gui/hud_slot_6.bmp", 60, 66, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("slot_item", "images/gui/hud_slot_action1.bmp", 60, 84, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("heart_beat", "images/gui/TEMP_beat_heart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("beat_blue", "images/gui/TEMP_beat_marker.bmp", 8, 50, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("beat_green", "images/gui/TEMP_beat_marker_green.bmp", 8, 50, 1, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("beat_red", "images/gui/TEMP_beat_marker_red.bmp", 8, 50, 1, 1, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("hud_slot_reload","images/gui/hud_slot_reload.bmp",60,84,1,1,true,RGB(255,0,255) );

	_loading->InitForImage("overlay_black", "images/gui/overlay_black.bmp", WINSIZEX, WINSIZEY, true, RGB(255,0,255));
	_loading->InitForImage("overlay_red", "images/gui/overlay_red.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->InitForImage("overlay_white", "images/gui/overlay_white.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->InitForImage("popup_back", "images/gui/popup_back.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loading->InitForImage("missedbeat", "images/option/enemybig_missedbeat.bmp", 92, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("coinmultiplier", "images/option/game_coinmultiplier.bmp", 81, 18, true, RGB(255, 0, 255));

	// GUI 숫자 이미지
	
	_loading->InitForFrameImage("TEMP_digits","images/gui/TEMP_digits.bmp",132,16,11,1,true,RGB(255,0,255));
	_loading->InitForFrameImage("TEMP_digits2", "images/gui/TEMP_digits_big.bmp", 264, 32, 11, 1, true, RGB(255, 0, 255));
	_loading->InitForImage("X","images/gui/X.bmp",8,8,true,RGB(255,0,255));

	// 몬스터 ui

	_loading->InitForImage("TEMP_heart_empty_small","images/gui/TEMP_heart_empty_small.bmp", 24, 24, true,RGB(255,0,255));
	_loading->InitForImage("TEMP_heart_small", "images/gui/TEMP_heart_small.bmp", 24, 24, true, RGB(255, 0, 255));


	_loading->InitForImage("head_black", "images/effect/head_black.bmp", 18, 18, true, RGB(255, 0, 255));
	_loading->InitForImage("head_yellow", "images/effect/head_yellow.bmp", 18, 18, true, RGB(255, 0, 255));

	// 여기는 옵션 창 관련

	_loading->InitForImage("border_corner1", "images/option/border_corner1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("border_corner2", "images/option/border_corner2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("border_corner3", "images/option/border_corner3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("border_corner4", "images/option/border_corner4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("border_horizontal", "images/option/border_horizontal.bmp", 960, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("border_vertical", "images/option/border_vertical.bmp", 48, 960, true, RGB(255, 0, 255));
	_loading->InitForImage("options_audiooptions", "images/option/options_audiooptions.bmp", 116, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_audiooptions_2", "images/option/options_audiooptions_2.bmp", 144, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_audiooptionstitle", "images/option/options_audiooptionstitle.bmp", 248, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("options_continue", "images/option/options_continue.bmp", 94, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_continue_s", "images/option/options_continue_s.bmp", 118, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_done", "images/option/options_done.bmp", 44, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_done_s", "images/option/options_done_s.bmp", 68, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_exitgame", "images/option/options_exitgame.bmp", 94, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_exitgame_s", "images/option/options_exitgame_s.bmp", 118, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_musicvolume", "images/option/options_musicvolume.bmp", 96, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_musicvolume_s", "images/option/options_musicvolume_s.bmp", 130, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_pause", "images/option/options_pause.bmp", 248, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("options_quickrestart", "images/option/options_quickrestart.bmp", 116, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_quickrestart_s", "images/option/options_quickrestart_s.bmp", 144, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_quit_lobby", "images/option/options_quit_lobby.bmp", 138, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_quit_lobby_s", "images/option/options_quit_lobby_s.bmp", 162, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_soundvolume", "images/option/options_soundvolume.bmp", 118, 24, true, RGB(255, 0, 255));
	_loading->InitForImage("options_soundvolume_s", "images/option/options_soundvolume_s.bmp", 142, 24, true, RGB(255, 0, 255));

	_loading->InitForImage("runsummary", "images/option/runsummary.bmp", 204, 48, true, RGB(255, 0, 255));
	_loading->InitForImage("game_score", "images/option/game_score.bmp", 102, 24, true, RGB(255, 0, 255));

	// 각종 이펙트 (아이템 이펙트, 몬스터 공격 이펙트 )

	_loading->InitForFrameImage("swipe_arrow_D", "images/effect/swipe_arrow_D.bmp", 28, 288, 1, 6, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_arrow_L", "images/effect/swipe_arrow_L.bmp", 288, 28, 6, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_arrow_R", "images/effect/swipe_arrow_R.bmp", 288, 28, 6, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_arrow_U", "images/effect/swipe_arrow_U.bmp", 28, 288, 1, 6, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_blunderbuss_D", "images/effect/swipe_blunderbuss_D.bmp", 218, 1408, 1, 8, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_blunderbuss_L", "images/effect/swipe_blunderbuss_L.bmp", 1408, 218, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_blunderbuss_R", "images/effect/swipe_blunderbuss_R.bmp", 1408, 218, 8, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_blunderbuss_U", "images/effect/swipe_blunderbuss_U.bmp", 218, 1408, 1, 8, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_broadsword_D", "images/effect/swipe_broadsword_D.bmp", 144, 144, 1, 3, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_broadsword_L", "images/effect/swipe_broadsword_L.bmp", 144, 144, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_broadsword_R", "images/effect/swipe_broadsword_R.bmp", 144, 144, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_broadsword_U", "images/effect/swipe_broadsword_U.bmp", 144, 144, 1, 3, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_dagger_D", "images/effect/swipe_dagger_D.bmp", 48, 144, 1, 3, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_dagger_L", "images/effect/swipe_dagger_L.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_dagger_R", "images/effect/swipe_dagger_R.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_dagger_U", "images/effect/swipe_dagger_U.bmp", 48, 144, 1, 3, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_enemy_D", "images/effect/swipe_enemy_D.bmp", 48, 270, 1, 5, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_L", "images/effect/swipe_enemy_L.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_R", "images/effect/swipe_enemy_R.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_U", "images/effect/swipe_enemy_U.bmp", 48, 270, 1, 5, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_flail_D", "images/effect/swipe_flail_D.bmp", 158, 590, 1, 5, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_flail_L", "images/effect/swipe_flail_L.bmp", 590, 158, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_flail_R", "images/effect/swipe_flail_R.bmp", 590, 158, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_flail_U", "images/effect/swipe_flail_U.bmp", 158, 590, 1, 5, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_longsword_D", "images/effect/swipe_longsword_D.bmp", 48, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_longsword_L", "images/effect/swipe_longsword_L.bmp", 384, 38, 4, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_longsword_R", "images/effect/swipe_longsword_R.bmp", 384, 48, 4, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_longsword_U", "images/effect/swipe_longsword_U.bmp", 48, 384, 1, 4, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("swipe_rapier_D", "images/effect/swipe_rapier_D.bmp", 48, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_rapier_L", "images/effect/swipe_rapier_L.bmp", 384, 48, 4, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_rapier_R", "images/effect/swipe_rapier_R.bmp", 384, 48, 4, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_rapier_U", "images/effect/swipe_rapier_U.bmp", 48, 384, 1, 4, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("TEMP_swipe_spear_D", "images/effect/TEMP_swipe_spear_D.bmp", 46, 288, 1, 6, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("TEMP_swipe_spear_L", "images/effect/TEMP_swipe_spear_L.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("TEMP_swipe_spear_R", "images/effect/TEMP_swipe_spear_R.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("TEMP_swipe_spear_U", "images/effect/TEMP_swipe_spear_U.bmp", 46, 288, 1, 6, true, RGB(255, 0, 255));

	// 몬스터 공격하는 이펙트
	_loading->InitForFrameImage("swipe_enemy_D", "images/effect/swipe_enemy_D.bmp", 48, 270, 1, 5, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_L", "images/effect/swipe_enemy_L.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_R", "images/effect/swipe_enemy_R.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("swipe_enemy_U", "images/effect/swipe_enemy_U.bmp", 48, 270, 1, 5, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("fire0", "images/effect/fire0.bmp", 728, 52, 14,1, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("fire1", "images/effect/fire1.bmp", 364, 52, 7, 1, true, RGB(255, 0, 255));

	// 체력회복 파티클
	_loading->InitForImage("TEMP_particle_confuse","images/effect/TEMP_particle_confuse.bmp",10,10,true,RGB(255,0,255));

	// 플레이어 

	_loading->InitForFrameImage("player_head", "images/player/player1_heads.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->InitForFrameImage("player_body", "images/player/player1_armor_body.bmp", 384, 480, 8, 10, true, RGB(255, 0, 255));

	// 섀도우

	_loading->InitForImage("shadow_small","images/player/TEMP_shadow_standard.bmp",48,54,true,RGB(255, 0, 255));
	_loading->InitForImage("shadow_large", "images/player/TEMP_shadow_large.bmp", 48, 56,true, RGB(255, 0, 255));

	_loading->InitForImage("black", "images/black.bmp",1000,1000);
	_loading->InitForImage("white","images/option/white.bmp",200,8);

	// 상점 주인과 횃불

	_loading->InitForFrameImage("shopkeeper", "images/monster/shopkeeper.bmp", 752, 152, 8, 2, true, RGB(255,0,255));
	_loading->InitForFrameImage("wall_torch", "images/level/wall_torch.bmp", 96, 52, 4, 1, true, RGB(255,0,255));


	// 킹콩가와 좀비

	_loading->InitForImage("king_conga_throne", "images/monster/boss/king_conga_throne.bmp", 88, 156, true, RGB(255, 0, 255));

	_loading->InitForFrameImage("king_conga","images/monster/boss/king_conga.bmp", 1044, 316, 9, 2, true,RGB(255,0,255));
	_loading->InitForFrameImage("zombie_snake", "images/monster/boss/zombie_snake.bmp", 3456, 100, 72, 2, true, RGB(255, 0, 255));

	// 킹 콩가 인트로 
	_loading->InitForImage("bg_bottomblade", "images/monster/boss/bg_bottomblade.bmp", 728, 96, true, RGB(255, 0, 255));
	_loading->InitForImage("bg_gradient", "images/monster/boss/bg_gradient.bmp", 960, 296, true, RGB(255, 0, 255));
	_loading->InitForImage("bg_topblade", "images/monster/boss/bg_topblade.bmp", 602, 68, true, RGB(255, 0, 255));
	_loading->InitForImage("bosscreen", "images/monster/boss/bosscreen_kingconga.bmp", 960, 390, true, RGB(255, 0, 255));
	_loading->InitForImage("bossName", "images/monster/boss/boss_kingcongasplash.bmp", 140, 48, true, RGB(255, 0, 255));
	
	
	//_loading->InitForImage("", "images/monster/boss/.bmp", , , true, RGB(255, 0, 255));


	// 사운드

	//SOUNDMANAGER->AddSound("lobby", "sound/lobby.ogg", true, true); // 로비
	//SOUNDMANAGER->AddSound("zone1_1", "sound/zone1_1.ogg", true, true); // zone1
	//SOUNDMANAGER->AddSound("zone1_2", "sound/zone1_2.ogg", true, true);
	//SOUNDMANAGER->AddSound("zone1_3", "sound/zone1_3.ogg", true, true);
	//
	//SOUNDMANAGER->AddSound("zone2_1", "sound/zone2_1.ogg", true, true); // zone2
	//SOUNDMANAGER->AddSound("zone2_2", "sound/zone2_2.ogg", true, true);
	//SOUNDMANAGER->AddSound("zone2_3", "sound/zone2_3.ogg", true, true);
	
	_loading->InitForSound("lobby","sound/lobby.ogg",true,true);
	_loading->InitForSound("zone1_1", "sound/zone1_1.ogg", true, true);
	_loading->InitForSound("zone1_2", "sound/zone1_2.ogg", true, true);
	_loading->InitForSound("zone1_3", "sound/zone1_3.ogg", true, true);
	
	_loading->InitForSound("boss_1", "sound/boss_1.ogg", true, true);

	// 플레이어 관련 사운드
	
	_loading->InitForSound("vo_p_death","sound/player/vo_cad_death_02.ogg",false,false);
	_loading->InitForSound("vo_p_dig", "sound/player/vo_cad_dig_03.ogg", false, false);
	_loading->InitForSound("vo_p_heal", "sound/player/vo_cad_heal_03.ogg", false, false);
	_loading->InitForSound("vo_p_hurt", "sound/player/vo_cad_hurt_01.ogg", false, false);
	_loading->InitForSound("vo_p_melee", "sound/player/vo_cad_melee_1_01.ogg", false, false);
	_loading->InitForSound("vo_p_ranged", "sound/player/vo_cad_ranged_01.ogg", false, false);
	
	
	// 몬스터 관련 사운드 ///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 밴시
	_loading->InitForSound("en_banshee_attack", "sound/monster/en_banshee_attack.ogg", false, false);
	_loading->InitForSound("en_banshee_cry", "sound/monster/en_banshee_cry.ogg", false, false);
	_loading->InitForSound("en_banshee_death", "sound/monster/en_banshee_death.ogg", false, false);
	_loading->InitForSound("en_banshee_hit_01", "sound/monster/en_banshee_hit_01.ogg", false, false);
	_loading->InitForSound("en_banshee_loop", "sound/monster/en_banshee_loop.ogg", false, true);
	// 박쥐
	_loading->InitForSound("en_bat_attack", "sound/monster/en_bat_attack.ogg", false, false);
	_loading->InitForSound("en_bat_death", "sound/monster/en_bat_death.ogg", false, false);
	_loading->InitForSound("en_bat_hit", "sound/monster/en_bat_hit.ogg", false, false);
	//박쥐 미니 보스
	_loading->InitForSound("en_bat_miniboss_attack", "sound/monster/en_bat_miniboss_attack.ogg", false, false);
	_loading->InitForSound("en_bat_miniboss_death", "sound/monster/en_bat_miniboss_death.ogg", false, false);
	_loading->InitForSound("en_bat_miniboss_hit", "sound/monster/en_bat_miniboss_hit.ogg", false, false);
	_loading->InitForSound("en_bat_miniboss_cry", "sound/monster/en_vampbat_cry.ogg", false, false);


	// 용
	_loading->InitForSound("en_dragon_attack_fire", "sound/monster/en_dragon_attack_fire.ogg", false, false);
	_loading->InitForSound("en_dragon_attack_melee", "sound/monster/en_dragon_attack_melee.ogg", false, false);
	_loading->InitForSound("en_dragon_attack_prefire", "sound/monster/en_dragon_attack_prefire.ogg", false, false);
	_loading->InitForSound("en_dragon_cry", "sound/monster/en_dragon_cry.ogg", false, false);
	_loading->InitForSound("en_dragon_death", "sound/monster/en_dragon_death.ogg", false, false);
	_loading->InitForSound("en_dragon_hit", "sound/monster/en_dragon_hit_01.ogg", false, false);
	_loading->InitForSound("en_dragon_walk_01", "sound/monster/en_dragon_walk_01.ogg", false, false);
	// 미노타우스
	_loading->InitForSound("en_minotaur_attack", "sound/monster/en_minotaur_attack.ogg", false, false);
	_loading->InitForSound("en_minotaur_charge", "sound/monster/en_minotaur_charge.ogg", false, false);
	_loading->InitForSound("en_minotaur_cry", "sound/monster/en_minotaur_cry.ogg", false, false);
	_loading->InitForSound("en_minotaur_death", "sound/monster/en_minotaur_death.ogg", false, false);
	_loading->InitForSound("en_minotaur_hit", "sound/monster/en_minotaur_hit.ogg", false, false);
	_loading->InitForSound("en_minotaur_wallimpact", "sound/monster/en_minotaur_wallimpact.ogg", false, false);
	// 상점 주인
	_loading->InitForSound("en_shopkeep_norm_death_01", "sound/monster/en_shopkeep_norm_death_01.ogg", false, false);
	_loading->InitForSound("en_shopkeep_norm_hit_01", "sound/monster/en_shopkeep_norm_hit_01.ogg", false, false);
	// 스켈레톤
	_loading->InitForSound("en_skel_attack_melee", "sound/monster/en_skel_attack_melee.ogg", false, false);
	_loading->InitForSound("en_skel_death", "sound/monster/en_skel_death.ogg", false, false);
	_loading->InitForSound("en_skel_hit", "sound/monster/en_skel_hit_01.ogg", false, false);
	// 슬라임
	_loading->InitForSound("en_slime_attack", "sound/monster/en_slime_attack.ogg", false, false);
	_loading->InitForSound("en_slime_death", "sound/monster/en_slime_death.ogg", false, false);
	_loading->InitForSound("en_slime_hit", "sound/monster/en_slime_hit.ogg", false, false);
	
	// 킹 콩가

	_loading->InitForSound("en_kingconga_attack_01", "sound/monster/en_kingconga_attack_01.ogg", false, false);
	_loading->InitForSound("en_kingconga_cry_01", "sound/monster/en_kingconga_cry_01.ogg", false, false);
	_loading->InitForSound("en_kingconga_death", "sound/monster/en_kingconga_death.ogg", false, false);
	_loading->InitForSound("en_kingconga_hit_01", "sound/monster/en_kingconga_hit_01.ogg", false, false);

	// 좀비 (킹 콩가 쫄 )

	_loading->InitForSound("en_zombie_attack", "sound/monster/en_zombie_attack.ogg", false, false);
	_loading->InitForSound("en_zombie_death", "sound/monster/en_zombie_death.ogg", false, false);


	// 다른 기타 사운드 효과음들  ///////////////////////////////////////////////////////////////////////////////////////////////////
	
	_loading->InitForSound("mov_dig_brick", "sound/soundEffect/mov_dig_brick.ogg", false, false);
	_loading->InitForSound("mov_dig_dirt", "sound/soundEffect/mov_dig_dirt.ogg", false, false);
	_loading->InitForSound("mov_dig_fail", "sound/soundEffect/mov_dig_fail.ogg", false, false);
	_loading->InitForSound("mov_dig_stone", "sound/soundEffect/mov_dig_stone.ogg", false, false);
	_loading->InitForSound("obj_door_open", "sound/soundEffect/obj_door_open.ogg", false, false);
	_loading->InitForSound("sfx_bomb_explode", "sound/soundEffect/sfx_bomb_explode.ogg", false, false);
	_loading->InitForSound("sfx_bomb_lit", "sound/soundEffect/sfx_bomb_lit.ogg", false, false);
	_loading->InitForSound("sfx_chain_break_ST", "sound/soundEffect/sfx_chain_break_ST.ogg", false, false);
	_loading->InitForSound("sfx_chain_groove_ST", "sound/soundEffect/sfx_chain_groove_ST.ogg", false, false);
	_loading->InitForSound("sfx_glass_break", "sound/soundEffect/sfx_glass_break.ogg", false, false);
	_loading->InitForSound("sfx_item_food", "sound/soundEffect/sfx_item_food.ogg", false, false);
	_loading->InitForSound("sfx_pickup_armor", "sound/soundEffect/sfx_pickup_armor.ogg", false, false);
	_loading->InitForSound("sfx_pickup_gold_01", "sound/soundEffect/sfx_pickup_gold_01.ogg", false, false);
	_loading->InitForSound("sfx_pickup_purchase", "sound/soundEffect/sfx_pickup_purchase.ogg", false, false);
	_loading->InitForSound("sfx_pickup_weapon", "sound/soundEffect/sfx_pickup_weapon.ogg", false, false);
	_loading->InitForSound("sfx_player_death_ST", "sound/soundEffect/sfx_player_death_ST.ogg", false, false);
	_loading->InitForSound("sfx_player_hit_ST", "sound/soundEffect/sfx_player_hit_ST.ogg", false, false);
	_loading->InitForSound("sfx_ui_back", "sound/soundEffect/sfx_ui_back.ogg", false, false);
	_loading->InitForSound("sfx_ui_select_down", "sound/soundEffect/sfx_ui_select_down.ogg", false, false);
	_loading->InitForSound("sfx_ui_select_up", "sound/soundEffect/sfx_ui_select_up.ogg", false, false);
	_loading->InitForSound("sfx_ui_start", "sound/soundEffect/sfx_ui_start.ogg", false, false);
	_loading->InitForSound("sfx_ui_toggle", "sound/soundEffect/sfx_ui_toggle.ogg", false, false);
	_loading->InitForSound("wep_spell_wind", "sound/soundEffect/wep_spell_wind.ogg", false, false);
	_loading->InitForSound("wep_fire", "sound/soundEffect/wep_fire.ogg", false, false);
	_loading->InitForSound("wep_reload", "sound/soundEffect/wep_reload.ogg", false, false);
	
	// 보스 아나운스 

	_loading->InitForSound("vo_announcer_kingconga", "sound/monster/vo_announcer_kingconga.ogg", false, false);
	////


	// 상점 아저씨 노래 사운드 파일

	_loading->InitForSound("zone1_1_shopkeeper", "sound/shopkeeper/zone1_1_shopkeeper.ogg", true, false);
	_loading->InitForSound("zone1_2_shopkeeper", "sound/shopkeeper/zone1_2_shopkeeper.ogg", true, false);
	_loading->InitForSound("zone1_3_shopkeeper", "sound/shopkeeper/zone1_3_shopkeeper.ogg", true, false);
	_loading->InitForSound("zone2_1_shopkeeper", "sound/shopkeeper/zone2_1_shopkeeper.ogg", true, false);
	_loading->InitForSound("zone2_2_shopkeeper", "sound/shopkeeper/zone2_2_shopkeeper.ogg", true, false);
	_loading->InitForSound("zone2_3_shopkeeper", "sound/shopkeeper/zone2_3_shopkeeper.ogg", true, false);

	_loading->InitForSound("boss_1","sound/boss_1.ogg",true,true);
	_loading->InitForSound("boss_2", "sound/boss_2.ogg", true, true);

	SOUNDMANAGER->SetBit("zone1_1");
	SOUNDMANAGER->SetBit("zone1_2");
	SOUNDMANAGER->SetBit("zone1_3");
	SOUNDMANAGER->SetBit("zone2_1");
	
}	
