#include "lw_usb/GenericMacros.h"
#include "lw_usb/GenericTypeDefs.h"

#include "platform.h"
#include "xparameters.h"
#include "xtmrctr.h"
#include "hdmi_text_controller.h"

#include "lw_usb/MAX3421E.h"
#include "lw_usb/USB.h"
#include "lw_usb/usb_ch9.h"
#include "lw_usb/transfer.h"
#include "lw_usb/HID.h"

#pragma GCC optimize ("Os")

#define HID_KEYBOARD 1
#define HID_MOUSE    2

#define KEY_RIGHT    0x4F  // 79
#define KEY_LEFT     0x50  // 80
#define KEY_DOWN     0x51  // 81
#define KEY_UP       0x52  // 82
#define KEY_Z        0x1D
#define KEY_X        0x1B
#define KEY_ENTER    0x28
#define KEY_MOD_SHIFT 0x22

#define SCREEN_W     256
#define SCREEN_H     240
#define PLAYER_W     24
#define PLAYER_H     16
#define PLAYER_HIT_INSET_X 3
#define PLAYER_HIT_INSET_Y 2
#define PLAYER_SPEED 3
#define PLAYER_MOVE_PERIOD_MS 33
#define PLAYER_BOUND_LEFT      16
#define PLAYER_BOUND_RIGHT     16
#define PLAYER_BOUND_TOP       32
#define PLAYER_BOUND_BOTTOM    16
#define PLAYER_LAUNCH_START_Y  156
#define PLAYER_LAUNCH_UP_Y     96
#define PLAYER_LAUNCH_DOWN_Y   200
#define PLAYER_LANDING_X       120
#define PLAYER_LANDING_Y       PLAYER_LAUNCH_START_Y
#define PLAYER_LAUNCH_DONE     0xFF
#define PLAYER_ROLL_DONE       0xFF
#define PLAYER_ROLL_COUNT      3
#define PLAYER_ROLL_STEP       1
#define PLAYER_ROLL_TICKS      15
#define PLAYER_ROLL_HOLD_TICKS 15
#define BULLET_W     8
#define BULLET_H     8
#define BULLET_SPEED 8
#define BULLET_COOLDOWN_MS 160
#define MAX_PLAYER_BULLETS 3
#define MAX_ENEMY_BULLETS 3
#define ENEMY_BULLET_SPEED 3
#define ENEMY_W     16
#define ENEMY_H     16
#define ENEMY_HIT_INSET_X 2
#define ENEMY_HIT_INSET_Y 2
#define ENEMY_SPEED 2
#define ENEMY_REVERSE_SPEED 1
#define ENEMY_DRIFT_SPEED 1
#define ENEMY_SIDE_SPEED 2
#define ENEMY_SIDE_DIAG_DX 1
#define ENEMY_SIDE_DIAG_DY 1
#define ENEMY_SIDE_VERTICAL_MIN_TICKS 10
#define ENEMY_SIDE_TURN_TICKS 6
#define ENEMY_SIDE_DIR_RIGHT 0x01
#define ENEMY_SIDE_TICK_SHIFT 1
#define ENEMY_SIDE_TICK_MASK 0x3E
#define ENEMY_SIDE_MODE_VERTICAL 0x40
#define ENEMY_SIDE_MODE_TURN 0x80
#define ENEMY_SIDE_MODE_TURN_TO_VERTICAL (ENEMY_SIDE_MODE_VERTICAL | ENEMY_SIDE_MODE_TURN)
#define ENEMY_SIDE_MODE_TURN_TO_HORIZONTAL ENEMY_SIDE_MODE_TURN
#define ENEMY_SIDE_STEP(dir_right) ((dir_right) ? ENEMY_SIDE_SPEED : -ENEMY_SIDE_SPEED)
#define ENEMY_SIDE_TURN_STEP(dir_right) ((dir_right) ? 1 : -1)
#define ENEMY_SPAWN_PERIOD_MS 900
#define LEVEL1_MAX_NORMAL_ENEMIES 4
#define LEVEL2_MAX_NORMAL_ENEMIES 8
#define LEVEL3_MAX_NORMAL_ENEMIES 14
#define GOLD_FORMATION_SIZE 5
#define GOLD_SPAWN_PROGRESS 240U
#define GOLD_START_X -64
#define GOLD_START_Y 48
#define GOLD_SPACING 24
#define GOLD_LOOP_STAGE_TICKS 8
#define GOLD_LOOP_TICKS 64
#define GOLD_LOOP_PLANE_DELAY 8
#define GOLD_LOOP_PHASE_TICKS (GOLD_LOOP_TICKS + ((GOLD_FORMATION_SIZE - 1) * GOLD_LOOP_PLANE_DELAY) + 8)
#define GOLD_BETWEEN_LOOPS_TICKS 14
#define BOSS_SPAWN_PROGRESS 900U
#define BOSS_START_X 104
#define BOSS_TARGET_Y 56
#define BOSS_HP 9
#define BOSS_DEATH_TICKS 60
#define BOSS_DEATH_HOLD_TICKS 45
#define BOSS_BURST_COOLDOWN 80
#define BOSS_BURST_GAP 8
#define BOSS_W 47
#define BOSS_H 40
#define BOSS_PATROL_LEFT 8
#define BOSS_PATROL_RIGHT (SCREEN_W - BOSS_W - 8)
#define BOSS_EXIT_TICKS 900
#define BOSS_END_PROGRESS_GAP 180U
#define MEDIUM_SPAWN_PROGRESS 1500U
#define MEDIUM_HP 5
#define MEDIUM_W 32
#define MEDIUM_H 32
#define MEDIUM_DEATH_TICKS 44
#define MEDIUM_DEATH_HOLD_TICKS 36
#define MEDIUM_TURN_TICKS 6
#define MEDIUM_STRAIGHT_MIN_TICKS 32
#define MEDIUM_TURN_TO_VERTICAL 0x80
#define MEDIUM_TURN_MASK 0x7F
#define LEVEL_COUNT 3
#define PLAYER_START_LIVES 3
#define PLAYER_RESPAWN_PAUSE_UPDATES 60
#define GAME_OVER_DIGIT_PERIOD_UPDATES 15
#define GAME_OVER_HOLD_UPDATES 90
#define CONGRATS_START_DELAY_UPDATES 60
#define CONGRATS_DIGIT_PERIOD_UPDATES 15
#define CONGRATS_HOLD_UPDATES 120
#define LEVEL_EASY_END_UPDATES   3600U
#define LEVEL_MEDIUM_END_UPDATES 3600U
#define LEVEL_HARD_END_UPDATES   3600U
#define MAX_ENEMIES 14
#define EXPLOSION_FRAMES 8
#define PLAYER_EXPLOSION_FRAMES 16
#define ENEMY_ANIM_FRAMES 8
#define ENEMY_PATTERN_MASK 0x07
#define ENEMY_ANIM_KIND_SHIFT 3
#define ENEMY_ANIM_FRAME_SHIFT 5
#define TIMER_TICKS_PER_MS 100000U
#define PLAYER_MOVE_PERIOD_TICKS (PLAYER_MOVE_PERIOD_MS * TIMER_TICKS_PER_MS)
#define BULLET_COOLDOWN_TICKS (BULLET_COOLDOWN_MS * TIMER_TICKS_PER_MS)
#define ENEMY_SPAWN_PERIOD_TICKS (ENEMY_SPAWN_PERIOD_MS * TIMER_TICKS_PER_MS)
#define LANDING_PAUSE_UPDATES 30
#define KBD_POLL_PERIOD_TICKS (8U * TIMER_TICKS_PER_MS)
#define USB_ENUM_SERVICE_PERIOD_TICKS (20U * TIMER_TICKS_PER_MS)

#define OAM_BASE_REG        0
#define OAM_PLAYER_SPRITE   0
#define OAM_BULLET_BASE     1
#define OAM_ENEMY_BULLET_BASE (OAM_BULLET_BASE + MAX_PLAYER_BULLETS)
#define OAM_ENEMY_BASE      (OAM_ENEMY_BULLET_BASE + MAX_ENEMY_BULLETS)
#define OAM_SCORE_BASE      21
#define OAM_START_ICON      27
#define OAM_POWERUP         28
#define OAM_GOLD_BONUS      29
#define OAM_ROLL_COUNT      30
#define OAM_LIVES_TENS      31
#define OAM_LIVES_ONES      32
#define OAM_LEVEL_TENS      33
#define OAM_LEVEL_ONES      34
#define OAM_PLAYER_NUMBER   35
#define OAM_ROLL_BONUS_BASE 36
#define OAM_ACCURACY_PERCENT_BASE 40
#define OAM_ACCURACY_BONUS_BASE 42
#define OAM_HIGH_SCORE_BASE 46
#define OAM_KILLS_BASE      52
#define OAM_DEATH_ACCURACY_BASE 57
#define OAM_CONGRATS_BASE   45
#define CONGRATS_CHARS      15
#define CONGRATS_X          68
#define CONGRATS_Y          116
#define SCORE_DIGITS        6
#define SCORE_X             24
#define SCORE_Y             24
#define GAMEPLAY_SCORE_X    33
#define GAMEPLAY_SCORE_Y    33
#define GAMEPLAY_P2_SCORE_X 178
#define HIGH_SCORE_X        105
#define HIGH_SCORE_Y        24
#define KILLS_X             169
#define KILLS_Y             64
#define DEATH_ACCURACY_X    185
#define DEATH_ACCURACY_Y    80
#define ROLL_COUNT_X        225
#define ROLL_COUNT_Y        209
#define OVERLAY_LIVES_X     49
#define OVERLAY_LIVES_Y     209
#define OVERLAY_LEVEL_X     97
#define OVERLAY_LEVEL_Y     89
#define OVERLAY_PLAYER_X    153
#define OVERLAY_PLAYER_Y    137
#define STATS_ROLL_BONUS_X  121
#define STATS_ROLL_BONUS_Y  183
#define STATS_ACCURACY_X    112
#define STATS_ACCURACY_Y    71
#define STATS_ACCURACY_BONUS_X 96
#define STATS_ACCURACY_BONUS_Y 135
#define GOLD_BONUS_POPUP_TICKS 30
#define POINTS_SMALL_ENEMY  50U
#define POINTS_GOLD_ENEMY   100U
#define POINTS_GOLD_CLEAR   500U
#define POINTS_MEDIUM_ENEMY 1000U
#define POINTS_BOSS_ENEMY   2000U
#define POINTS_POWERUP      1000U
#define START_ICON_X        65
#define START_ICON_TOP_Y    124
#define START_ICON_BOTTOM_Y 141

#define GAME_REG_BASE       64
#define GAME_REG_FLAGS      0
#define GAME_REG_SOUND      1
#define GAME_REG_SCROLL_Y   7
#define GAME_FLAG_INTRO_OVERLAY 0x01U
#define GAME_FLAG_START_SCREEN 0x02U
#define GAME_FLAG_STATS_OVERLAY 0x04U
#define GAME_FLAG_FREEZE_SCROLL 0x08U
#define GAME_FLAG_DEATH_SCREEN 0x10U
#define GAME_FLAG_BLACK_SCREEN 0x20U
#define GAME_FLAG_PLAYER2_ACTIVE 0x40U
#define SOUND_SHOOT       1U
#define HW_SCROLL_WRAP_Y    2096U
#define LEVEL_LANDING_START_SCROLL_Y (HW_SCROLL_WRAP_Y - 64U)
#define LEVEL_LANDING_STOP_SCROLL_Y  (HW_SCROLL_WRAP_Y - 1U)

#define OAM_ATTR_PALETTE_MASK  0x03
#define OAM_ATTR_PRIORITY      0x20
#define OAM_ATTR_FLIP_H        0x40
#define OAM_ATTR_FLIP_V        0x80

#define OAM_PALETTE_0          0x00
#define OAM_PALETTE_1          0x01
#define OAM_PALETTE_2          0x02
#define OAM_PALETTE_3          0x03

#define TILE_SUPERACE_1     28
#define TILE_SUPERACE_RUN   3
#define TILE_START_ICON     22
#define TILE_PLAYER_BULLET  44
#define TILE_PLAYER_BULLET_POWER 45
#define TILE_ENEMY_BULLET   46
#define TILE_POWERUP        65
#define TILE_ENEMY_BASIC    0
#define TILE_ENEMY_SIDE_DIAG 10
#define TILE_ENEMY_SIDE_H    12
#define TILE_ENEMY_SIDE_V    13
#define TILE_ENEMY_MEDIUM_DIAG 33
#define TILE_ENEMY_MEDIUM_V    34
#define TILE_ENEMY_MEDIUM_H    35
#define TILE_BOSS_GREEN      129
#define TILE_EXPLOSION_0    66
#define TILE_EXPLOSION_1    70
#define TILE_EXPLOSION_2    69
#define TILE_EXPLOSION_3    68
#define TILE_EXPLOSION(frame) ((u8)((0x44454642U >> (((frame) >> 1U) * 8U)) & 0xFFU))
#define TILE_DIGIT(digit) ((digit) == 0 ? 124 : (u8)(114 + (digit)))

typedef signed short coord_t;

typedef struct {
    coord_t x;
    coord_t y;
    u8 active;
    u8 explosion_frame;
} PlayerBullet;

typedef struct {
    coord_t x;
    coord_t y;
    signed char dx;
    signed char dy;
    u8 active;
} EnemyBullet;

typedef struct {
    coord_t x;
    coord_t y;
    u8 active;
} Powerup;

typedef struct {
    coord_t x;
    coord_t y;
    u8 life;
    u8 active;
    u8 explosion_frame;
    signed char dx;
    signed char dy;
    u8 motion;
    u8 type;
} Enemy;

extern HID_DEVICE hid_device;
extern XTmrCtr Usb_timer;

static BYTE addr = 1;
static coord_t player_x = 120;
static coord_t player_y = 200;
static PlayerBullet player_bullets[MAX_PLAYER_BULLETS];
static EnemyBullet enemy_bullets[MAX_ENEMY_BULLETS];
static Powerup powerup;
static Enemy enemies[MAX_ENEMIES];
static u32 last_fire_ms = 0;
static u32 last_enemy_spawn_ticks = 0;
static u8 enemy_spawn_index = 0;
static u8 random_state = 0x5AU;
static u8 player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
static u8 player_active = 1;
static u8 player_launch_phase = 0;
static u8 player_launch_timer = 0;
static u8 player_roll_phase = PLAYER_ROLL_DONE;
static u8 player_roll_timer = 0;
static u8 player_rolls_available = PLAYER_ROLL_COUNT;
static coord_t player_roll_origin_y = 0;
static u8 roll_x_was_down = 0;
static u8 player_lives = PLAYER_START_LIVES;
static u8 player_respawn_timer = 0;
static u8 start_screen_active = 1;
static u8 start_selection_bottom = 0;
static u8 start_shift_was_down = 0;
static u8 game_over_active = 0;
static u8 game_over_timer = 0;
static u8 game_over_kill_digits = 0;
static u8 game_over_accuracy_digits = 0;
static u8 game_over_hold_timer = 0;
static u8 congrats_active = 0;
static u8 congrats_start_delay = 0;
static u8 congrats_timer = 0;
static u8 congrats_visible_chars = 0;
static u8 congrats_hold_timer = 0;
static u8 landing_active = 0;
static u8 landing_scroll_frozen = 0;
static u8 landing_pause_updates = 0;
static u8 current_level = 0;
static u16 level_progress_updates = 0;
static u8 gold_formation_spawned = 0;
static u8 gold_formation_alive = 0;
static coord_t gold_base_x = GOLD_START_X;
static coord_t gold_base_y = GOLD_START_Y;
static signed char gold_dx = 3;
static signed char gold_dy = 0;
static u8 gold_route_phase = 0;
static u8 gold_route_tick = 0;
static u8 boss_spawned = 0;
static u8 medium_spawned = 0;
static u8 boss_exit_active = 0;
static u16 boss_flight_ticks = 0;
static u8 boss_burst_cooldown = BOSS_BURST_COOLDOWN;
static u8 boss_burst_remaining = 0;
static u8 boss_burst_gap = 0;
static u8 power_bullets_active = 0;
static u32 score = 0;
static u16 shots_fired = 0;
static u16 shots_hit = 0;
static u16 total_shots_fired = 0;
static u16 total_shots_hit = 0;
static u8 stats_accuracy_percent = 0;
static u16 stats_roll_bonus = 0;
static u16 stats_accuracy_bonus = 0;
static u32 high_score = 0;
static u16 enemies_killed = 0;
static coord_t gold_bonus_x = 0;
static coord_t gold_bonus_y = 0;
static u8 gold_bonus_ticks = 0;
static u8 gold_bonus_tile = 47;
static u8 pending_powerup_after_bonus = 0;
static u32 sound_command = 0;
static u8 two_player_mode = 0;
static u8 active_player = 0;
static u8 player_done_mask = 0;
static u32 player_scores[2] = {0, 0};
static u16 player_total_shots_fired[2] = {0, 0};
static u16 player_total_shots_hit[2] = {0, 0};
static u16 player_enemies_killed[2] = {0, 0};
static u8 player_lives_store[2] = {PLAYER_START_LIVES, PLAYER_START_LIVES};
static u8 player_level_store[2] = {0, 0};

enum {
    ENEMY_TYPE_BASIC = 0,
    ENEMY_TYPE_SIDE = 1,
    ENEMY_TYPE_GOLD = 2,
    ENEMY_TYPE_BOSS = 3,
    ENEMY_TYPE_MEDIUM = 4
};

static u8 make_oam_attributes(u8 palette, int behind_background, int flip_h, int flip_v);
static void write_game_reg(u32 reg_index, u32 value);
static u32 read_game_reg(u32 reg_index);
static int boxes_overlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);
static int player_is_exploding(void);
static void spawn_powerup_at(int x, int y);
static void show_game_over_screen(void);
static void update_game_over_screen(void);
static void show_congrats_screen(void);
static void update_congrats_screen(void);

static u32 player_flag(void)
{
    return (two_player_mode && active_player != 0) ? GAME_FLAG_PLAYER2_ACTIVE : 0U;
}

static void write_game_flags(u32 flags)
{
    write_game_reg(GAME_REG_FLAGS, flags | player_flag());
}

static void play_sound(u32 sound_id)
{
    write_game_reg(GAME_REG_SOUND, 0U);
    sound_command++;
    if (sound_command == 0) {
        sound_command = 1;
    }
    write_game_reg(GAME_REG_SOUND, (sound_command << 8) | (sound_id & 0xFFU));
}

static void play_shoot_sound(void)
{
    play_sound(SOUND_SHOOT);
}

static void save_active_player_state(void)
{
    player_scores[active_player] = score;
    player_total_shots_fired[active_player] = total_shots_fired;
    player_total_shots_hit[active_player] = total_shots_hit;
    player_enemies_killed[active_player] = enemies_killed;
    player_lives_store[active_player] = player_lives;
    player_level_store[active_player] = current_level;
}

static void load_active_player_state(void)
{
    score = player_scores[active_player];
    total_shots_fired = player_total_shots_fired[active_player];
    total_shots_hit = player_total_shots_hit[active_player];
    enemies_killed = player_enemies_killed[active_player];
    player_lives = player_lives_store[active_player];
    current_level = player_level_store[active_player];
}

static u32 best_player_score(void)
{
    return player_scores[0] > player_scores[1] ? player_scores[0] : player_scores[1];
}

static void add_score(u32 points)
{
    score += points;
    if (score > 999999U) {
        score = 999999U;
    }
    if (score > high_score) {
        high_score = score;
    }
}

static u32 enemy_point_value(u8 enemy_type)
{
    if (enemy_type == ENEMY_TYPE_BOSS) {
        return POINTS_BOSS_ENEMY;
    }
    if (enemy_type == ENEMY_TYPE_MEDIUM) {
        return POINTS_MEDIUM_ENEMY;
    }
    if (enemy_type == ENEMY_TYPE_GOLD) {
        return POINTS_GOLD_ENEMY;
    }
    if (enemy_type == ENEMY_TYPE_BASIC || enemy_type == ENEMY_TYPE_SIDE) {
        return POINTS_SMALL_ENEMY;
    }

    return 0U;
}

static BYTE GetDriverandReport(void)
{
    BYTE i;
    BYTE device = 0xFF;
    DEV_RECORD* tpl_ptr;

    for (i = 1; i < USB_NUMDEVICES; i++) {
        tpl_ptr = GetDevtable(i);
        if (tpl_ptr->epinfo != NULL) {
            device = tpl_ptr->devclass;
        }
    }

    return device;
}

static int key_is_down(const BOOT_KBD_REPORT* kbd, BYTE keycode)
{
    for (int i = 0; i < 6; i++) {
        if (kbd->keycode[i] == keycode) {
            return 1;
        }
    }

    return 0;
}

static int shift_is_down(const BOOT_KBD_REPORT* kbd)
{
    return (kbd->mod & KEY_MOD_SHIFT) != 0;
}

static void clamp_player_to_screen(void)
{
    const int min_x = PLAYER_BOUND_LEFT;
    const int max_x = SCREEN_W - PLAYER_BOUND_RIGHT - PLAYER_W;
    const int min_y = PLAYER_BOUND_TOP;
    const int max_y = SCREEN_H - PLAYER_BOUND_BOTTOM - PLAYER_H;

    if (player_x < min_x) {
        player_x = min_x;
    } else if (player_x > max_x) {
        player_x = max_x;
    }

    if (player_y < min_y) {
        player_y = min_y;
    } else if (player_y > max_y) {
        player_y = max_y;
    }
}

static void update_player_from_keyboard(const BOOT_KBD_REPORT* kbd)
{
    if (key_is_down(kbd, KEY_LEFT)) {
        player_x -= PLAYER_SPEED;
    }

    if (key_is_down(kbd, KEY_RIGHT)) {
        player_x += PLAYER_SPEED;
    }

    if (key_is_down(kbd, KEY_UP)) {
        player_y -= PLAYER_SPEED;
    }

    if (key_is_down(kbd, KEY_DOWN)) {
        player_y += PLAYER_SPEED;
    }

    clamp_player_to_screen();
}

static void update_player_x_from_keyboard(const BOOT_KBD_REPORT* kbd)
{
    if (key_is_down(kbd, KEY_LEFT)) {
        player_x -= PLAYER_SPEED;
    }

    if (key_is_down(kbd, KEY_RIGHT)) {
        player_x += PLAYER_SPEED;
    }

    clamp_player_to_screen();
}

static void fire_player_bullet(u32 now_ticks)
{
    if ((u32)(now_ticks - last_fire_ms) < BULLET_COOLDOWN_TICKS) {
        return;
    }

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (!player_bullets[i].active) {
            player_bullets[i].active = 1;
            player_bullets[i].explosion_frame = 0;
            player_bullets[i].x = player_x + (PLAYER_W / 2) - (BULLET_W / 2);
            player_bullets[i].y = player_y - BULLET_H;
            shots_fired++;
            total_shots_fired++;
            last_fire_ms = now_ticks;
            play_shoot_sound();
            return;
        }
    }
}

static void update_player_bullets(void)
{
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (player_bullets[i].active) {
            if (player_bullets[i].active == 2) {
                if (player_bullets[i].explosion_frame < 3) {
                    player_bullets[i].explosion_frame++;
                } else {
                    player_bullets[i].active = 0;
                }

                continue;
            }

            player_bullets[i].y -= BULLET_SPEED;

            if (player_bullets[i].y < 0) {
                player_bullets[i].active = 0;
            }
        }
    }
}

static u8 next_random(void)
{
    random_state = (u8)((random_state << 1) ^ ((random_state & 0x80) ? 0x1DU : 0U));
    return random_state;
}

static void fire_enemy_bullet(const Enemy* enemy)
{
    int tx = player_x - enemy->x;
    int ty = player_y - enemy->y;

    if (ty <= 0 || tx * 3 > ty * 2 || tx * 3 < -ty * 2) {
        return;
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (!enemy_bullets[i].active) {
            enemy_bullets[i].active = 1;
            enemy_bullets[i].x = enemy->x + (ENEMY_W / 2) - (BULLET_W / 2);
            enemy_bullets[i].y = enemy->y + ENEMY_H;
            enemy_bullets[i].dx = tx < -32 ? -2 : tx > 32 ? 2 : tx < -12 ? -1 : tx > 12 ? 1 : 0;
            enemy_bullets[i].dy = ENEMY_BULLET_SPEED;
            return;
        }
    }
}

static void fire_green_enemy_bullet(const Enemy* enemy)
{
    int tx = player_x - enemy->x;
    int ty = player_y - enemy->y;

    if (tx > -16 && tx < 16 && ty > -16 && ty < 16) {
        return;
    }

    if (tx > 0 && tx * 3 < ty) {
        return;
    }

    if (tx < 0 && tx * 3 > -ty) {
        return;
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (!enemy_bullets[i].active) {
            enemy_bullets[i].active = 1;
            enemy_bullets[i].x = enemy->x + (ENEMY_W / 2) - (BULLET_W / 2);
            enemy_bullets[i].y = enemy->y + (ENEMY_H / 2) - (BULLET_H / 2);
            enemy_bullets[i].dx = tx < -32 ? -ENEMY_BULLET_SPEED : tx > 32 ? ENEMY_BULLET_SPEED :
                                  tx < -12 ? -2 : tx > 12 ? 2 : 0;
            enemy_bullets[i].dy = ty < -32 ? -ENEMY_BULLET_SPEED : ty > 32 ? ENEMY_BULLET_SPEED :
                                  ty < -12 ? -2 : ty > 12 ? 2 : 0;

            if (enemy_bullets[i].dx == 0 && enemy_bullets[i].dy == 0) {
                enemy_bullets[i].dx = tx < 0 ? -2 : 2;
            }

            return;
        }
    }
}

static void fire_boss_bullet(const Enemy* enemy)
{
    int tx = (player_x + (PLAYER_W / 2)) - (enemy->x + (BOSS_W / 2));

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (!enemy_bullets[i].active) {
            enemy_bullets[i].active = 1;
            enemy_bullets[i].x = enemy->x + (BOSS_W / 2) - (BULLET_W / 2);
            enemy_bullets[i].y = enemy->y + BOSS_H - BULLET_H;
            enemy_bullets[i].dx = tx < -48 ? -ENEMY_BULLET_SPEED :
                                  tx > 48 ? ENEMY_BULLET_SPEED :
                                  tx < -20 ? -2 :
                                  tx > 20 ? 2 :
                                  tx < -8 ? -1 :
                                  tx > 8 ? 1 : 0;
            enemy_bullets[i].dy = ENEMY_BULLET_SPEED;
            return;
        }
    }
}

static void update_boss_burst(const Enemy* enemy)
{
    if (boss_burst_remaining == 0) {
        if (boss_burst_cooldown != 0) {
            boss_burst_cooldown--;
        } else {
            boss_burst_remaining = 3;
            boss_burst_gap = 0;
        }
    }

    if (boss_burst_remaining != 0) {
        if (boss_burst_gap != 0) {
            boss_burst_gap--;
        } else {
            fire_boss_bullet(enemy);
            boss_burst_remaining--;
            boss_burst_gap = BOSS_BURST_GAP;

            if (boss_burst_remaining == 0) {
                boss_burst_cooldown = BOSS_BURST_COOLDOWN;
            }
        }
    }
}

static void reset_game_state(void)
{
    player_x = 120;
    player_y = PLAYER_LAUNCH_START_Y;
    player_active = 1;
    player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
    player_launch_phase = 0;
    player_launch_timer = 0;
    player_roll_phase = PLAYER_ROLL_DONE;
    player_roll_timer = 0;
    player_rolls_available = PLAYER_ROLL_COUNT;
    player_roll_origin_y = player_y;
    roll_x_was_down = 0;
    player_lives = PLAYER_START_LIVES;
    player_respawn_timer = 0;
    start_screen_active = 1;
    start_selection_bottom = 0;
    start_shift_was_down = 0;
    game_over_active = 0;
    game_over_timer = 0;
    game_over_kill_digits = 0;
    game_over_accuracy_digits = 0;
    game_over_hold_timer = 0;
    congrats_active = 0;
    congrats_start_delay = 0;
    congrats_timer = 0;
    congrats_visible_chars = 0;
    congrats_hold_timer = 0;
    landing_active = 0;
    landing_scroll_frozen = 0;
    landing_pause_updates = 0;
    current_level = 0;
    level_progress_updates = 0;
    gold_formation_spawned = 0;
    gold_formation_alive = 0;
    gold_base_x = GOLD_START_X;
    gold_base_y = GOLD_START_Y;
    gold_dx = 3;
    gold_dy = 0;
    gold_route_phase = 0;
    gold_route_tick = 0;
    boss_spawned = 0;
    medium_spawned = 0;
    boss_exit_active = 0;
    boss_flight_ticks = 0;
    boss_burst_cooldown = BOSS_BURST_COOLDOWN;
    boss_burst_remaining = 0;
    boss_burst_gap = 0;
    power_bullets_active = 0;
    powerup.active = 0;
    score = 0;
    shots_fired = 0;
    shots_hit = 0;
    total_shots_fired = 0;
    total_shots_hit = 0;
    stats_accuracy_percent = 0;
    stats_roll_bonus = 0;
    stats_accuracy_bonus = 0;
    enemies_killed = 0;
    gold_bonus_ticks = 0;
    gold_bonus_tile = 47;
    pending_powerup_after_bonus = 0;
    sound_command = 0;
    two_player_mode = 0;
    active_player = 0;
    player_done_mask = 0;
    for (int i = 0; i < 2; i++) {
        player_scores[i] = 0;
        player_total_shots_fired[i] = 0;
        player_total_shots_hit[i] = 0;
        player_enemies_killed[i] = 0;
        player_lives_store[i] = PLAYER_START_LIVES;
        player_level_store[i] = 0;
    }
}

static void update_enemy_bullets(void)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (enemy_bullets[i].active) {
            enemy_bullets[i].x += enemy_bullets[i].dx;
            enemy_bullets[i].y += enemy_bullets[i].dy;

            if (enemy_bullets[i].y > SCREEN_H ||
                enemy_bullets[i].y < -BULLET_H ||
                enemy_bullets[i].x < -BULLET_W ||
                enemy_bullets[i].x > SCREEN_W) {
                enemy_bullets[i].active = 0;
            }
        }
    }
}

static void update_powerup(void)
{
    if (gold_bonus_ticks != 0) {
        gold_bonus_ticks--;
        if (gold_bonus_ticks == 0 && pending_powerup_after_bonus) {
            pending_powerup_after_bonus = 0;
            spawn_powerup_at(gold_bonus_x, gold_bonus_y);
        }
    }

    if (!powerup.active) {
        return;
    }

    powerup.y++;

    if (player_active && !player_is_exploding() &&
        boxes_overlap(player_x + PLAYER_HIT_INSET_X,
                      player_y + PLAYER_HIT_INSET_Y,
                      PLAYER_W - (PLAYER_HIT_INSET_X * 2),
                      PLAYER_H - (PLAYER_HIT_INSET_Y * 2),
                      powerup.x,
                      powerup.y,
                      ENEMY_W,
                      ENEMY_H)) {
        powerup.active = 0;
        power_bullets_active = 1;
        gold_bonus_x = powerup.x;
        gold_bonus_y = powerup.y;
        gold_bonus_tile = 91;
        gold_bonus_ticks = GOLD_BONUS_POPUP_TICKS;
        pending_powerup_after_bonus = 0;
        add_score(POINTS_POWERUP);
    } else if (powerup.y > SCREEN_H) {
        powerup.active = 0;
    }
}

static int boxes_overlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
    return (ax < bx + bw) &&
           (ax + aw > bx) &&
           (ay < by + bh) &&
           (ay + ah > by);
}

static int enemy_hit_w(const Enemy* enemy)
{
    if (enemy->type == ENEMY_TYPE_BOSS) {
        return BOSS_W;
    }
    if (enemy->type == ENEMY_TYPE_MEDIUM) {
        return MEDIUM_W;
    }

    return ENEMY_W;
}

static int enemy_hit_h(const Enemy* enemy)
{
    if (enemy->type == ENEMY_TYPE_BOSS) {
        return BOSS_H;
    }
    if (enemy->type == ENEMY_TYPE_MEDIUM) {
        return MEDIUM_H;
    }

    return ENEMY_H;
}

static int player_enemy_overlap(const Enemy* enemy)
{
    int inset_x = enemy->type == ENEMY_TYPE_BOSS ? 6 : enemy->type == ENEMY_TYPE_MEDIUM ? 5 : ENEMY_HIT_INSET_X;
    int inset_y = enemy->type == ENEMY_TYPE_BOSS ? 6 : enemy->type == ENEMY_TYPE_MEDIUM ? 5 : ENEMY_HIT_INSET_Y;

    return boxes_overlap(
        player_x + PLAYER_HIT_INSET_X,
        player_y + PLAYER_HIT_INSET_Y,
        PLAYER_W - (PLAYER_HIT_INSET_X * 2),
        PLAYER_H - (PLAYER_HIT_INSET_Y * 2),
        enemy->x + inset_x,
        enemy->y + inset_y,
        enemy_hit_w(enemy) - (inset_x * 2),
        enemy_hit_h(enemy) - (inset_y * 2));
}

static int player_bullet_overlap(const EnemyBullet* bullet)
{
    return boxes_overlap(
        player_x + PLAYER_HIT_INSET_X,
        player_y + PLAYER_HIT_INSET_Y,
        PLAYER_W - (PLAYER_HIT_INSET_X * 2),
        PLAYER_H - (PLAYER_HIT_INSET_Y * 2),
        bullet->x,
        bullet->y,
        BULLET_W,
        BULLET_H);
}

static int enemy_bullet_overlap(const Enemy* enemy, const PlayerBullet* bullet)
{
    int inset_x = enemy->type == ENEMY_TYPE_BOSS ? 6 : enemy->type == ENEMY_TYPE_MEDIUM ? 5 : ENEMY_HIT_INSET_X;
    int inset_y = enemy->type == ENEMY_TYPE_BOSS ? 6 : enemy->type == ENEMY_TYPE_MEDIUM ? 5 : ENEMY_HIT_INSET_Y;

    return boxes_overlap(
        bullet->x,
        bullet->y,
        BULLET_W,
        BULLET_H,
        enemy->x + inset_x,
        enemy->y + inset_y,
        enemy_hit_w(enemy) - (inset_x * 2),
        enemy_hit_h(enemy) - (inset_y * 2));
}

static int player_is_exploding(void)
{
    return player_explosion_frame < PLAYER_EXPLOSION_FRAMES;
}

static int player_is_launching(void)
{
    return !start_screen_active && !landing_active && player_launch_phase != PLAYER_LAUNCH_DONE;
}

static int player_is_landing(void)
{
    return landing_active != 0;
}

static int player_is_rolling(void)
{
    return player_roll_phase != PLAYER_ROLL_DONE;
}

static void clear_player_roll(void)
{
    player_roll_phase = PLAYER_ROLL_DONE;
    player_roll_timer = 0;
    player_roll_origin_y = player_y;
}

static void clear_active_objects(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = 0;
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        enemy_bullets[i].active = 0;
    }

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        player_bullets[i].active = 0;
    }

    powerup.active = 0;
    gold_bonus_ticks = 0;
    gold_bonus_tile = 47;
    pending_powerup_after_bonus = 0;
}

static void reset_level_enemy_state(void)
{
    level_progress_updates = 0;
    last_enemy_spawn_ticks = 0;
    enemy_spawn_index = 0;
    gold_formation_spawned = 0;
    gold_formation_alive = 0;
    gold_base_x = GOLD_START_X;
    gold_base_y = GOLD_START_Y;
    gold_dx = 3;
    gold_dy = 0;
    gold_route_phase = 0;
    gold_route_tick = 0;
    boss_spawned = 0;
    medium_spawned = 0;
    boss_exit_active = 0;
    boss_flight_ticks = 0;
    boss_burst_remaining = 0;
    boss_burst_gap = 0;
    boss_burst_cooldown = BOSS_BURST_COOLDOWN;
    shots_fired = 0;
    shots_hit = 0;
    stats_accuracy_percent = 0;
    stats_roll_bonus = 0;
    stats_accuracy_bonus = 0;
}

static void start_launch_sequence(void)
{
    u8 selected_two_players = start_selection_bottom;

    start_screen_active = 0;
    start_selection_bottom = 0;
    two_player_mode = selected_two_players;
    active_player = 0;
    player_done_mask = 0;
    game_over_active = 0;
    congrats_active = 0;
    congrats_start_delay = 0;
    congrats_timer = 0;
    congrats_visible_chars = 0;
    congrats_hold_timer = 0;
    clear_player_roll();
    player_x = 120;
    player_y = PLAYER_LAUNCH_START_Y;
    player_active = 1;
    player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
    player_launch_phase = 0;
    player_launch_timer = 0;
    landing_active = 0;
    landing_scroll_frozen = 0;
    landing_pause_updates = 0;
    player_respawn_timer = 0;
    player_rolls_available = PLAYER_ROLL_COUNT;
    player_lives = PLAYER_START_LIVES;
    roll_x_was_down = 0;
    power_bullets_active = 0;
    current_level = 0;
    score = 0;
    shots_fired = 0;
    shots_hit = 0;
    total_shots_fired = 0;
    total_shots_hit = 0;
    enemies_killed = 0;
    for (int i = 0; i < 2; i++) {
        player_scores[i] = 0;
        player_total_shots_fired[i] = 0;
        player_total_shots_hit[i] = 0;
        player_enemies_killed[i] = 0;
        player_lives_store[i] = PLAYER_START_LIVES;
        player_level_store[i] = 0;
    }
    clear_active_objects();
    reset_level_enemy_state();
    write_game_flags(GAME_FLAG_INTRO_OVERLAY);
}

static void restart_current_level_launch(void)
{
    start_screen_active = 0;
    game_over_active = 0;
    congrats_active = 0;
    congrats_start_delay = 0;
    congrats_timer = 0;
    congrats_visible_chars = 0;
    congrats_hold_timer = 0;
    clear_player_roll();
    player_x = 120;
    player_y = PLAYER_LAUNCH_START_Y;
    player_active = 1;
    player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
    player_launch_phase = 0;
    player_launch_timer = 0;
    player_respawn_timer = 0;
    player_rolls_available = PLAYER_ROLL_COUNT;
    roll_x_was_down = 0;
    power_bullets_active = 0;
    landing_active = 0;
    landing_scroll_frozen = 0;
    landing_pause_updates = 0;
    clear_active_objects();
    reset_level_enemy_state();
    write_game_flags(GAME_FLAG_INTRO_OVERLAY);
}

static int other_player_can_play(void)
{
    u8 other = active_player ^ 1U;

    return two_player_mode && !(player_done_mask & (1U << other)) && player_lives_store[other] != 0;
}

static void finish_run_to_title(void)
{
    u32 title_score;
    u32 title_high_score;

    save_active_player_state();
    title_score = two_player_mode ? player_scores[0] : score;
    title_high_score = two_player_mode ? best_player_score() : high_score;
    if (title_high_score > high_score) {
        high_score = title_high_score;
    }
    title_high_score = high_score;

    reset_game_state();
    score = title_score;
    high_score = title_high_score;
    write_game_reg(GAME_REG_FLAGS, GAME_FLAG_START_SCREEN);
}

static void switch_to_other_player_turn(void)
{
    active_player ^= 1U;
    load_active_player_state();
    restart_current_level_launch();
}

static void update_start_screen(const BOOT_KBD_REPORT* kbd, int have_report)
{
    u8 shift_down;

    if (!start_screen_active) {
        return;
    }

    shift_down = have_report && shift_is_down(kbd);
    if (shift_down && !start_shift_was_down) {
        start_selection_bottom ^= 1U;
    }
    start_shift_was_down = shift_down;

    if (have_report && key_is_down(kbd, KEY_ENTER)) {
        start_launch_sequence();
    }
}

static void clear_enemies_for_landing(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].life != 0) {
            enemies[i].life = 0;
            enemies[i].explosion_frame = 0;
            enemies[i].dx = 0;
            enemies[i].dy = 0;
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        enemy_bullets[i].active = 0;
    }
}

static u8 current_accuracy_percent(void)
{
    u32 percent;

    if (shots_fired == 0) {
        return 0;
    }

    percent = ((u32)shots_hit * 100U) / shots_fired;
    if (percent > 100U) {
        percent = 100U;
    }

    return (u8)percent;
}

static u8 total_accuracy_percent(void)
{
    u32 percent;

    if (total_shots_fired == 0) {
        return 0;
    }

    percent = ((u32)total_shots_hit * 100U) / total_shots_fired;
    if (percent > 100U) {
        percent = 100U;
    }

    return (u8)percent;
}

static void start_landing_sequence(void)
{
    landing_active = 1;
    landing_scroll_frozen = 0;
    landing_pause_updates = 0;
    player_active = 1;
    player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
    clear_player_roll();
    clear_enemies_for_landing();

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        player_bullets[i].active = 0;
    }

    powerup.active = 0;
    boss_exit_active = 0;
    boss_flight_ticks = 0;
    boss_burst_remaining = 0;
    boss_burst_gap = 0;
    boss_burst_cooldown = BOSS_BURST_COOLDOWN;
    stats_roll_bonus = (u16)player_rolls_available * 1000U;
    stats_accuracy_percent = current_accuracy_percent();
    if (stats_accuracy_percent > 99U) {
        stats_accuracy_percent = 99U;
    }
    stats_accuracy_bonus = (u16)stats_accuracy_percent * 100U;
    add_score(stats_roll_bonus);
    add_score(stats_accuracy_bonus);

    write_game_flags(GAME_FLAG_STATS_OVERLAY);
}

static void start_next_level_launch(void)
{
    if (current_level >= LEVEL_COUNT - 1) {
        return;
    }

    current_level++;
    clear_player_roll();
    player_rolls_available = PLAYER_ROLL_COUNT;
    player_respawn_timer = 0;
    player_x = 120;
    player_y = PLAYER_LAUNCH_START_Y;
    player_active = 1;
    player_explosion_frame = PLAYER_EXPLOSION_FRAMES;
    player_launch_phase = 0;
    player_launch_timer = 0;
    landing_active = 0;
    landing_scroll_frozen = 0;
    landing_pause_updates = 0;
    level_progress_updates = 0;
    gold_formation_spawned = 0;
    gold_formation_alive = 0;
    gold_base_x = GOLD_START_X;
    gold_base_y = GOLD_START_Y;
    gold_dx = 3;
    gold_dy = 0;
    gold_route_phase = 0;
    gold_route_tick = 0;
    boss_spawned = 0;
    medium_spawned = 0;
    boss_exit_active = 0;
    boss_flight_ticks = 0;
    boss_burst_remaining = 0;
    boss_burst_gap = 0;
    boss_burst_cooldown = BOSS_BURST_COOLDOWN;
    shots_fired = 0;
    shots_hit = 0;
    stats_accuracy_percent = 0;
    stats_roll_bonus = 0;
    stats_accuracy_bonus = 0;
    gold_bonus_ticks = 0;
    gold_bonus_tile = 47;
    pending_powerup_after_bonus = 0;

    write_game_flags(GAME_FLAG_INTRO_OVERLAY);
}

static void update_player_landing(void)
{
    u32 scroll_y;

    if (!player_is_landing()) {
        return;
    }

    if (!landing_scroll_frozen) {
        scroll_y = read_game_reg(GAME_REG_SCROLL_Y) & 0x0FFFU;
        if (scroll_y >= LEVEL_LANDING_STOP_SCROLL_Y) {
            landing_scroll_frozen = 1;
            write_game_flags(GAME_FLAG_STATS_OVERLAY | GAME_FLAG_FREEZE_SCROLL);
        }
    }

    if (player_x < PLAYER_LANDING_X) {
        player_x += player_x + 2 > PLAYER_LANDING_X ? PLAYER_LANDING_X - player_x : 2;
    } else if (player_x > PLAYER_LANDING_X) {
        player_x -= player_x - 2 < PLAYER_LANDING_X ? player_x - PLAYER_LANDING_X : 2;
    }

    if (player_y < PLAYER_LANDING_Y) {
        player_y += player_y + 2 > PLAYER_LANDING_Y ? PLAYER_LANDING_Y - player_y : 2;
    } else if (player_y > PLAYER_LANDING_Y) {
        player_y -= player_y - 2 < PLAYER_LANDING_Y ? player_y - PLAYER_LANDING_Y : 2;
    }

    if (landing_scroll_frozen && player_x == PLAYER_LANDING_X && player_y == PLAYER_LANDING_Y) {
        if (landing_pause_updates < LANDING_PAUSE_UPDATES) {
            landing_pause_updates++;
        } else if (current_level >= LEVEL_COUNT - 1) {
            show_congrats_screen();
        } else {
            start_next_level_launch();
        }
    }
}

static void update_level_progress(void)
{
    u32 scroll_y;

    if (landing_active || start_screen_active || player_is_launching() || player_is_exploding()) {
        return;
    }

    if (level_progress_updates != 0xFFFFU) {
        level_progress_updates++;
    }

    scroll_y = read_game_reg(GAME_REG_SCROLL_Y) & 0x0FFFU;
    if (scroll_y >= LEVEL_LANDING_START_SCROLL_Y) {
        start_landing_sequence();
    }
}

static void update_landing_enemy_explosions(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active || enemies[i].life != 0) {
            continue;
        }

        if (enemies[i].type == ENEMY_TYPE_BOSS &&
            enemies[i].explosion_frame < BOSS_DEATH_TICKS + BOSS_DEATH_HOLD_TICKS - 1) {
            enemies[i].explosion_frame++;
        } else if (enemies[i].type == ENEMY_TYPE_MEDIUM &&
                   enemies[i].explosion_frame < MEDIUM_DEATH_TICKS + MEDIUM_DEATH_HOLD_TICKS - 1) {
            enemies[i].explosion_frame++;
        } else if (enemies[i].type != ENEMY_TYPE_BOSS && enemies[i].type != ENEMY_TYPE_MEDIUM &&
                   enemies[i].explosion_frame < EXPLOSION_FRAMES - 1) {
            enemies[i].explosion_frame++;
        } else {
            enemies[i].active = 0;
        }
    }
}

static void start_player_explosion(void)
{
    clear_player_roll();
    player_active = 0;
    player_explosion_frame = 0;
    player_respawn_timer = 0;
    if (player_lives != 0) {
        player_lives--;
    }
    if (player_lives != 0) {
        player_respawn_timer = PLAYER_RESPAWN_PAUSE_UPDATES;
    }
    write_game_flags(0U);
}

static void update_player_explosion(void)
{
    if (player_is_exploding()) {
        player_explosion_frame++;
        if (!player_is_exploding() && player_lives == 0) {
            show_game_over_screen();
        }
    }
}

static void update_player_respawn(void)
{
    if (player_respawn_timer == 0) {
        return;
    }

    player_respawn_timer--;
    if (player_respawn_timer == 0) {
        save_active_player_state();
        if (other_player_can_play()) {
            switch_to_other_player_turn();
        } else {
            restart_current_level_launch();
        }
    }
}

static void show_game_over_screen(void)
{
    game_over_active = 1;
    start_screen_active = 0;
    landing_active = 0;
    player_active = 0;
    player_respawn_timer = 0;
    game_over_timer = 0;
    game_over_kill_digits = 0;
    game_over_accuracy_digits = 0;
    game_over_hold_timer = 0;
    clear_player_roll();
    clear_active_objects();
    write_game_flags(GAME_FLAG_DEATH_SCREEN);
}

static void update_game_over_screen(void)
{
    if (!game_over_active) {
        return;
    }

    if (game_over_kill_digits < 5) {
        game_over_timer++;
        if (game_over_timer >= GAME_OVER_DIGIT_PERIOD_UPDATES) {
            game_over_timer = 0;
            game_over_kill_digits++;
        }
        return;
    }

    if (game_over_accuracy_digits < 3) {
        game_over_timer++;
        if (game_over_timer >= GAME_OVER_DIGIT_PERIOD_UPDATES) {
            game_over_timer = 0;
            game_over_accuracy_digits++;
        }
        return;
    }

    if (game_over_hold_timer < GAME_OVER_HOLD_UPDATES) {
        game_over_hold_timer++;
        return;
    }

    player_done_mask |= 1U << active_player;
    save_active_player_state();
    if (other_player_can_play()) {
        switch_to_other_player_turn();
    } else {
        finish_run_to_title();
    }
}

static void show_congrats_screen(void)
{
    congrats_active = 1;
    congrats_start_delay = CONGRATS_START_DELAY_UPDATES;
    congrats_timer = 0;
    congrats_visible_chars = 0;
    congrats_hold_timer = 0;
    start_screen_active = 0;
    game_over_active = 0;
    landing_active = 0;
    player_active = 0;
    player_respawn_timer = 0;
    clear_player_roll();
    clear_active_objects();
    write_game_flags(GAME_FLAG_STATS_OVERLAY | GAME_FLAG_FREEZE_SCROLL);
}

static void update_congrats_screen(void)
{
    if (!congrats_active) {
        return;
    }

    if (congrats_start_delay != 0) {
        congrats_start_delay--;
        if (congrats_start_delay == 0) {
            write_game_flags(GAME_FLAG_BLACK_SCREEN | GAME_FLAG_FREEZE_SCROLL);
        }
        return;
    }

    if (congrats_visible_chars < CONGRATS_CHARS) {
        congrats_timer++;
        if (congrats_timer >= CONGRATS_DIGIT_PERIOD_UPDATES) {
            congrats_timer = 0;
            congrats_visible_chars++;
        }
        return;
    }

    if (congrats_hold_timer < CONGRATS_HOLD_UPDATES) {
        congrats_hold_timer++;
        return;
    }

    player_done_mask |= 1U << active_player;
    save_active_player_state();
    if (other_player_can_play()) {
        switch_to_other_player_turn();
    } else {
        finish_run_to_title();
    }
}

static void start_player_roll(void)
{
    if (player_rolls_available == 0 || player_is_rolling() || player_is_launching() ||
        player_is_landing() || player_is_exploding() || !player_active) {
        return;
    }

    player_rolls_available--;
    player_roll_phase = 0;
    player_roll_timer = 0;
    player_roll_origin_y = player_y;
}

static void update_player_roll(void)
{
    coord_t target_y;

    if (!player_is_rolling()) {
        return;
    }

    target_y = player_roll_origin_y;
    if (player_roll_phase == 0 || player_roll_phase == 1) {
        target_y = player_roll_origin_y - 8;
    } else if (player_roll_phase == 2 || player_roll_phase == 3) {
        target_y = player_roll_origin_y + 8;
    }

    if (player_y < target_y) {
        player_y += PLAYER_ROLL_STEP;
        if (player_y > target_y) {
            player_y = target_y;
        }
    } else if (player_y > target_y) {
        player_y -= PLAYER_ROLL_STEP;
        if (player_y < target_y) {
            player_y = target_y;
        }
    }

    clamp_player_to_screen();
    player_roll_timer++;

    if (player_roll_phase == 3) {
        if (player_roll_timer < PLAYER_ROLL_HOLD_TICKS) {
            return;
        }
    } else if (player_roll_timer < PLAYER_ROLL_TICKS) {
        return;
    }

    player_roll_timer = 0;
    player_roll_phase++;

    if (player_roll_phase > 5) {
        player_roll_phase = PLAYER_ROLL_DONE;
        player_y = player_roll_origin_y;
        clamp_player_to_screen();
    }
}

static u8 player_tile(void)
{
    static const u8 explosion_tiles[] = {42, 43, 69, 49, 50, 51, 52, 53};
    u8 phase = player_launch_phase;

    if (phase != PLAYER_LAUNCH_DONE) {
        if (phase == 0) return TILE_SUPERACE_RUN;
        if (phase == 1) return 28;
        if (phase == 2) return 29;
        if (phase == 3) return 30;
        if (phase == 4) return 32;
        if (phase == 5) return 39;
        if (phase == 6) return 40;
        if (phase == 7) return 31;
        if (phase == 8) return 41;
        return TILE_SUPERACE_1;
    }

    if (player_is_landing()) {
        return TILE_SUPERACE_RUN;
    }

    if (player_is_rolling()) {
        if (player_roll_phase == 0) return 29;
        if (player_roll_phase == 1) return 30;
        if (player_roll_phase == 2) return 32;
        if (player_roll_phase == 3) return 39;
        if (player_roll_phase == 4) return 40;
        if (player_roll_phase == 5) return 31;
    }

    return player_is_exploding() ? explosion_tiles[player_explosion_frame >> 1U] : (player_active ? TILE_SUPERACE_1 : 0);
}

static void update_player_launch(void)
{
    if (!player_is_launching()) {
        return;
    }

    if (player_launch_phase == 0) {
        if (player_y > PLAYER_LAUNCH_UP_Y) {
            player_y -= 2;
        } else {
            player_launch_phase = 1;
            player_launch_timer = 0;
        }

        return;
    }

    if (player_launch_phase >= 3 && player_launch_phase <= 6) {
        player_y += 1;
    } else if (player_launch_phase == 8) {
        if (player_y > PLAYER_BOUND_TOP) {
            player_y -= 2;
        }
        player_launch_timer++;
        if (player_launch_timer >= 12) {
            player_launch_phase = PLAYER_LAUNCH_DONE;
            write_game_flags(0U);
        }

        return;
    }

    player_launch_timer++;

    if ((player_launch_phase == 5 && player_launch_timer < 86) ||
        (player_launch_phase == 7 && player_launch_timer < 12) ||
        (player_launch_phase != 5 && player_launch_timer < 6)) {
        return;
    }

    player_launch_timer = 0;
    player_launch_phase++;

    if (player_launch_phase > 8) {
        player_launch_phase = PLAYER_LAUNCH_DONE;
        write_game_flags(0U);
    }
}

static u8 enemy_plane_tile(const Enemy* enemy)
{
    static const u8 anim_tiles[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 2, 4, 5, 5,
        5, 5, 4, 2, 1, 1, 0, 0,
        0, 0, 6, 6, 7, 7, 9, 9
    };
    u8 kind = (enemy->motion >> ENEMY_ANIM_KIND_SHIFT) & 0x03;
    u8 frame = enemy->motion >> ENEMY_ANIM_FRAME_SHIFT;

    return anim_tiles[(kind << 3) + frame];
}

static u8 enemy_side_tile(const Enemy* enemy)
{
    if (enemy->dx != 0 && enemy->dy != 0) {
        return TILE_ENEMY_SIDE_DIAG;
    }

    return enemy->dx != 0 ? TILE_ENEMY_SIDE_H : TILE_ENEMY_SIDE_V;
}

static u8 enemy_side_attributes(const Enemy* enemy)
{
    int flip_v = enemy->dx == 0 ? enemy->dy > 0 : enemy->dy < 0;
    return make_oam_attributes(OAM_PALETTE_1, 0, enemy->dx < 0, flip_v);
}

static u8 enemy_medium_tile(const Enemy* enemy)
{
    if (enemy->dx != 0 && enemy->dy != 0) {
        return TILE_ENEMY_MEDIUM_DIAG;
    }

    return enemy->dx != 0 ? TILE_ENEMY_MEDIUM_H : TILE_ENEMY_MEDIUM_V;
}

static u8 enemy_medium_attributes(const Enemy* enemy)
{
    int flip_h = enemy->dx < 0;
    int flip_v = 0;

    if (enemy->dx == 0) {
        flip_v = enemy->dy < 0;
    } else if (enemy->dy != 0) {
        flip_v = enemy->dy < 0;
    }

    return make_oam_attributes(OAM_PALETTE_0, 0, flip_h, flip_v);
}

static signed char enemy_side_saved_dx(const Enemy* enemy)
{
    return (enemy->motion & ENEMY_SIDE_DIR_RIGHT) ? ENEMY_SIDE_SPEED : -ENEMY_SIDE_SPEED;
}

static u8 active_normal_enemy_count(void)
{
    u8 count = 0;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].life != 0 &&
            (enemies[i].type == ENEMY_TYPE_BASIC || enemies[i].type == ENEMY_TYPE_SIDE)) {
            count++;
        }
    }

    return count;
}

static void spawn_powerup_at(int x, int y)
{
    powerup.active = 1;
    powerup.x = x;
    powerup.y = y;
}

static void show_gold_bonus_at(int x, int y)
{
    gold_bonus_x = x;
    gold_bonus_y = y;
    gold_bonus_tile = 47;
    gold_bonus_ticks = GOLD_BONUS_POPUP_TICKS;
    pending_powerup_after_bonus = 1;
}

static void set_gold_loop_motion(Enemy* enemy, u8 stage)
{
    switch (stage & 0x07) {
    case 0:
        enemy->dx = 2;
        enemy->dy = 2;
        break;
    case 1:
        enemy->dx = 0;
        enemy->dy = 3;
        break;
    case 2:
        enemy->dx = -2;
        enemy->dy = 2;
        break;
    case 3:
        enemy->dx = -3;
        enemy->dy = 0;
        break;
    case 4:
        enemy->dx = -2;
        enemy->dy = -2;
        break;
    case 5:
        enemy->dx = 0;
        enemy->dy = -3;
        break;
    case 6:
        enemy->dx = 2;
        enemy->dy = -2;
        break;
    default:
        enemy->dx = 3;
        enemy->dy = 0;
        break;
    }
}

static void maybe_spawn_gold_formation(void)
{
    u8 spawned = 0;

    if (current_level > 1 || gold_formation_spawned || level_progress_updates < GOLD_SPAWN_PROGRESS) {
        return;
    }

    for (int i = 0; i < MAX_ENEMIES && spawned < GOLD_FORMATION_SIZE; i++) {
        if (!enemies[i].active) {
            enemies[i].active = 1;
            enemies[i].life = 1;
            enemies[i].type = ENEMY_TYPE_GOLD;
            enemies[i].x = GOLD_START_X - (spawned * GOLD_SPACING);
            enemies[i].y = GOLD_START_Y;
            enemies[i].explosion_frame = EXPLOSION_FRAMES;
            enemies[i].dx = 3;
            enemies[i].dy = 0;
            enemies[i].motion = spawned;
            spawned++;
        }
    }

    if (spawned == GOLD_FORMATION_SIZE) {
        gold_formation_spawned = 1;
        gold_formation_alive = GOLD_FORMATION_SIZE;
        gold_base_x = GOLD_START_X;
        gold_base_y = GOLD_START_Y;
        gold_dx = 3;
        gold_dy = 0;
        gold_route_phase = 0;
        gold_route_tick = 0;
    } else {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active && enemies[i].type == ENEMY_TYPE_GOLD) {
                enemies[i].active = 0;
            }
        }
    }
}

static void update_gold_formation_path(void)
{
    if (!gold_formation_spawned || gold_formation_alive == 0) {
        return;
    }

    if (gold_route_phase == 0) {
        gold_dx = 3;
        gold_dy = 0;
        if (gold_base_x >= 72) {
            gold_route_phase = 1;
            gold_route_tick = 0;
        } else {
            gold_base_x += gold_dx;
        }
    } else if (gold_route_phase == 1 || gold_route_phase == 3) {
        gold_dx = 3;
        gold_dy = 0;
        gold_route_tick++;
        if (gold_route_tick >= GOLD_LOOP_PHASE_TICKS) {
            gold_route_phase++;
            gold_route_tick = 0;
        }
    } else if (gold_route_phase == 2) {
        gold_dx = 3;
        gold_dy = 0;
        gold_route_tick++;
        if (gold_route_tick >= GOLD_BETWEEN_LOOPS_TICKS) {
            gold_route_phase = 3;
            gold_route_tick = 0;
        }
    } else {
        gold_dx = 3;
        gold_dy = 0;
    }
}

static void maybe_spawn_boss(void)
{
    u8 max_bosses;
    u16 threshold;

    if (current_level == 0) {
        max_bosses = 1;
        threshold = 2700U;
    } else if (current_level == 1) {
        max_bosses = 2;
        threshold = 2350U + ((u16)boss_spawned * 500U);
    } else {
        max_bosses = 5;
        threshold = boss_spawned < 2 ? 1500U + ((u16)boss_spawned * 600U) : 3000U;
    }

    while (boss_spawned < max_bosses && level_progress_updates >= threshold) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                coord_t boss_x = BOSS_START_X;

                if (current_level == 2 && boss_spawned >= 2) {
                    boss_x = 44 + ((boss_spawned - 2U) * 56);
                } else if (boss_spawned & 0x01) {
                    boss_x = 64;
                } else if (boss_spawned != 0) {
                    boss_x = 144;
                }

                enemies[i].active = 1;
                enemies[i].life = BOSS_HP;
                enemies[i].type = ENEMY_TYPE_BOSS;
                enemies[i].x = boss_x;
                enemies[i].y = SCREEN_H + ((boss_spawned & 0x01) ? 24 : 0);
                enemies[i].explosion_frame = EXPLOSION_FRAMES;
                enemies[i].dx = 0;
                enemies[i].dy = -1;
                enemies[i].motion = 0;
                boss_spawned++;
                boss_exit_active = 0;
                boss_flight_ticks = 0;
                break;
            }

            if (i == MAX_ENEMIES - 1) {
                return;
            }
        }

        if (current_level == 1) {
            threshold = 2350U + ((u16)boss_spawned * 500U);
        } else if (current_level == 2) {
            threshold = boss_spawned < 2 ? 1500U + ((u16)boss_spawned * 600U) : 3000U;
        }
    }
}

static void maybe_spawn_medium_enemy(void)
{
    u8 max_mediums = current_level == 0 ? 2U : current_level == 1 ? 4U : 6U;
    u16 start = current_level == 0 ? 900U : current_level == 1 ? 700U : 600U;
    u16 gap = current_level == 0 ? 900U : current_level == 1 ? 600U : 400U;

    while (medium_spawned < max_mediums && level_progress_updates >= start + ((u16)medium_spawned * gap)) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].active = 1;
                enemies[i].life = MEDIUM_HP;
                enemies[i].type = ENEMY_TYPE_MEDIUM;
                enemies[i].x = 32 + ((medium_spawned * 43U) & 0x9FU);
                enemies[i].y = -MEDIUM_H - ((medium_spawned & 0x01) ? 18 : 0);
                enemies[i].dx = 0;
                enemies[i].dy = 1;
                enemies[i].explosion_frame = EXPLOSION_FRAMES;
                enemies[i].motion = MEDIUM_STRAIGHT_MIN_TICKS + (next_random() & 0x1F);
                medium_spawned++;
                break;
            }

            if (i == MAX_ENEMIES - 1) {
                return;
            }
        }
    }
}

static int spawn_side_enemy(void)
{
    u8 from_left = (next_random() & 0x01) == 0;
    u8 diagonal = (next_random() & 0x01) == 0;
    u8 max_normal = current_level == 0 ? LEVEL1_MAX_NORMAL_ENEMIES :
                    current_level == 1 ? LEVEL2_MAX_NORMAL_ENEMIES : LEVEL3_MAX_NORMAL_ENEMIES;

    if (active_normal_enemy_count() >= max_normal) {
        return 0;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].active = 1;
            enemies[i].life = 1;
            enemies[i].type = ENEMY_TYPE_SIDE;
            enemies[i].x = from_left ? -ENEMY_W : SCREEN_W;
            enemies[i].y = 48 + (next_random() & 0x7F);
            enemies[i].explosion_frame = EXPLOSION_FRAMES;
            enemies[i].dx = diagonal ? (from_left ? ENEMY_SIDE_DIAG_DX : -ENEMY_SIDE_DIAG_DX) :
                                       (from_left ? ENEMY_SIDE_SPEED : -ENEMY_SIDE_SPEED);
            enemies[i].dy = diagonal ? (player_y < enemies[i].y ? -ENEMY_SIDE_DIAG_DY : ENEMY_SIDE_DIAG_DY) : 0;
            enemies[i].motion = from_left ? 1 : 0;
            return 1;
        }
    }

    return 0;
}

static void spawn_enemy(u32 now_ticks)
{
    static const u8 spawn_x[] = {32, 96, 160, 208, 64, 136};
    u8 pattern;
    u8 formation_count;
    u8 formation_roll;
    u8 formation_style;
    u8 formation_slot;
    u8 max_normal = current_level == 0 ? LEVEL1_MAX_NORMAL_ENEMIES :
                    current_level == 1 ? LEVEL2_MAX_NORMAL_ENEMIES : LEVEL3_MAX_NORMAL_ENEMIES;
    coord_t x;
    coord_t y;

    if ((u32)(now_ticks - last_enemy_spawn_ticks) < ENEMY_SPAWN_PERIOD_TICKS) {
        return;
    }

    if ((next_random() & 0x01) == 0) {
        spawn_side_enemy();
    }

    if (active_normal_enemy_count() >= max_normal) {
        last_enemy_spawn_ticks = now_ticks;
        return;
    }

    pattern = enemy_spawn_index;
    formation_roll = next_random() & 0x07;
    formation_count = formation_roll < 2 ? 1 : formation_roll < 5 ? 2 : 3;
    {
        u8 normal_count = active_normal_enemy_count();
        u8 normal_slots = normal_count >= max_normal ? 0 : max_normal - normal_count;

        if (formation_count > normal_slots) {
            formation_count = normal_slots;
        }

        if (formation_count == 0) {
            last_enemy_spawn_ticks = now_ticks;
            return;
        }
    }
    formation_style = next_random() & 0x03;
    formation_slot = 0;

    x = spawn_x[pattern];
    if (formation_count != 1) {
        x -= 16;
        if (x < PLAYER_BOUND_LEFT) {
            x = PLAYER_BOUND_LEFT;
        } else if (x > 176) {
            x = 176;
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].active = 1;
            enemies[i].life = 1;
            enemies[i].type = ENEMY_TYPE_BASIC;
            enemies[i].x = x;
            y = -ENEMY_H;
            if (formation_count != 1) {
                if (formation_style == 0) {
                    y -= (formation_slot & 0x01) ? 10 : 0;
                } else if (formation_style == 1) {
                    y -= formation_slot * 8;
                } else if (formation_style == 2) {
                    y -= formation_slot == 1 ? 12 : 0;
                } else {
                    y -= formation_slot == 0 ? 8 : formation_slot == 2 ? 8 : 0;
                }
            }
            enemies[i].y = y;
            enemies[i].explosion_frame = EXPLOSION_FRAMES;
            enemies[i].dx = 0;
            enemies[i].dy = ENEMY_SPEED;
            enemies[i].motion = pattern;

            if (pattern == 1) {
                enemies[i].dx = ENEMY_DRIFT_SPEED;
            } else if (pattern == 2) {
                enemies[i].dx = -ENEMY_DRIFT_SPEED;
            }

            x += 20;
            formation_slot++;
            formation_count--;
            if (formation_count != 0) {
                continue;
            }

            enemy_spawn_index++;
            if (enemy_spawn_index >= 6) {
                enemy_spawn_index = 0;
            }
            last_enemy_spawn_ticks = now_ticks;
            return;
        }
    }

    enemy_spawn_index++;
    if (enemy_spawn_index >= 6) {
        enemy_spawn_index = 0;
    }
    last_enemy_spawn_ticks = now_ticks;
}

static void update_enemies(u32 now_ticks)
{
    maybe_spawn_gold_formation();
    update_gold_formation_path();
    maybe_spawn_boss();
    maybe_spawn_medium_enemy();
    spawn_enemy(now_ticks);

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            if (enemies[i].life == 0) {
                if (enemies[i].type == ENEMY_TYPE_BOSS &&
                    enemies[i].explosion_frame < BOSS_DEATH_TICKS + BOSS_DEATH_HOLD_TICKS - 1) {
                    enemies[i].explosion_frame++;
                } else if (enemies[i].type == ENEMY_TYPE_MEDIUM &&
                    enemies[i].explosion_frame < MEDIUM_DEATH_TICKS + MEDIUM_DEATH_HOLD_TICKS - 1) {
                    enemies[i].explosion_frame++;
                } else if (enemies[i].type != ENEMY_TYPE_BOSS && enemies[i].explosion_frame < EXPLOSION_FRAMES - 1) {
                    enemies[i].explosion_frame++;
                } else {
                    enemies[i].active = 0;
                }

                continue;
            }

            if (enemies[i].type == ENEMY_TYPE_MEDIUM) {
                signed char move_x = enemies[i].dx;
                signed char move_y = enemies[i].dy;

                if ((enemies[i].dx != 0 && enemies[i].dy != 0) && ((enemies[i].motion & MEDIUM_TURN_MASK) == 0)) {
                    if (enemies[i].motion & MEDIUM_TURN_TO_VERTICAL) {
                        enemies[i].dx = 0;
                    } else {
                        enemies[i].dy = 0;
                    }
                    enemies[i].motion = MEDIUM_STRAIGHT_MIN_TICKS + (next_random() & 0x1F);
                } else if ((enemies[i].motion & MEDIUM_TURN_MASK) != 0) {
                    enemies[i].motion--;
                } else if (enemies[i].x > 24 && enemies[i].x < SCREEN_W - MEDIUM_W - 24 &&
                           enemies[i].y > 32 && enemies[i].y < SCREEN_H - MEDIUM_H - 32 &&
                           (next_random() & 0x03) == 0) {
                    if (enemies[i].dx != 0) {
                        enemies[i].dy = (next_random() & 0x01) ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TO_VERTICAL | MEDIUM_TURN_TICKS;
                    } else {
                        enemies[i].dx = (next_random() & 0x01) ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TICKS;
                    }
                } else {
                    enemies[i].motion = MEDIUM_STRAIGHT_MIN_TICKS;
                }

                if (level_progress_updates <= MEDIUM_SPAWN_PROGRESS + 900U &&
                    (enemies[i].dx == 0 || enemies[i].dy == 0)) {
                    if (enemies[i].x < 20 && enemies[i].dx < 0) {
                        enemies[i].dy = enemies[i].y < SCREEN_H / 2 ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TO_VERTICAL | MEDIUM_TURN_TICKS;
                    } else if (enemies[i].x > SCREEN_W - MEDIUM_W - 20 && enemies[i].dx > 0) {
                        enemies[i].dy = enemies[i].y < SCREEN_H / 2 ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TO_VERTICAL | MEDIUM_TURN_TICKS;
                    }
                    if (enemies[i].y < 24 && enemies[i].dy < 0) {
                        enemies[i].dx = enemies[i].x < SCREEN_W / 2 ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TICKS;
                    } else if (enemies[i].y > SCREEN_H - MEDIUM_H - 24 && enemies[i].dy > 0) {
                        enemies[i].dx = enemies[i].x < SCREEN_W / 2 ? 1 : -1;
                        enemies[i].motion = MEDIUM_TURN_TICKS;
                    }
                }

                move_x = enemies[i].dx;
                move_y = enemies[i].dy;
                if (move_x != 0 && move_y != 0) {
                    if (level_progress_updates & 0x01) {
                        move_x = 0;
                    } else {
                        move_y = 0;
                    }
                }

                enemies[i].x += move_x;
                enemies[i].y += move_y;

                if (level_progress_updates > MEDIUM_SPAWN_PROGRESS + 900U &&
                    (enemies[i].x < -MEDIUM_W || enemies[i].x > SCREEN_W ||
                     enemies[i].y < -MEDIUM_H || enemies[i].y > SCREEN_H)) {
                    enemies[i].active = 0;
                }

                continue;
            }

            if (enemies[i].type == ENEMY_TYPE_BOSS) {
                u8 boss_tick = enemies[i].motion + 1U;

                enemies[i].motion = boss_tick;
                if (enemies[i].y > BOSS_TARGET_Y) {
                    if ((boss_tick & 0x01) == 0) {
                        enemies[i].y--;
                    }
                    enemies[i].dx = 0;
                    enemies[i].dy = -1;
                } else {
                    if (boss_exit_active) {
                        enemies[i].x += enemies[i].dx;
                        enemies[i].dy = 0;
                        if (enemies[i].x < -BOSS_W || enemies[i].x > SCREEN_W) {
                            enemies[i].active = 0;
                        }

                        continue;
                    }

                    if (boss_flight_ticks < BOSS_EXIT_TICKS) {
                        boss_flight_ticks++;
                    } else {
                        boss_exit_active = 1;
                        boss_burst_remaining = 0;
                        boss_burst_gap = 0;
                        boss_burst_cooldown = BOSS_BURST_COOLDOWN;
                        if (enemies[i].dx == 0) {
                            enemies[i].dx = 1;
                        }
                        enemies[i].dy = 0;
                        continue;
                    }

                    if (enemies[i].dx == 0) {
                        enemies[i].dx = 1;
                    }

                    enemies[i].x += enemies[i].dx;

                    if ((boss_tick & 0x07) == 0) {
                        if (boss_tick & 0x10) {
                            enemies[i].y--;
                        } else {
                            enemies[i].y++;
                        }
                    }

                    if (enemies[i].x < BOSS_PATROL_LEFT) {
                        enemies[i].x = BOSS_PATROL_LEFT;
                        enemies[i].dx = 1;
                    } else if (enemies[i].x > BOSS_PATROL_RIGHT) {
                        enemies[i].x = BOSS_PATROL_RIGHT;
                        enemies[i].dx = -1;
                    }

                    if (enemies[i].y < 44) {
                        enemies[i].y = 44;
                    } else if (enemies[i].y > 70) {
                        enemies[i].y = 70;
                    }

                    update_boss_burst(&enemies[i]);
                }

                continue;
            }

            if (enemies[i].type == ENEMY_TYPE_SIDE || enemies[i].type == ENEMY_TYPE_GOLD) {
                if (enemies[i].type == ENEMY_TYPE_GOLD) {
                    if (gold_route_phase == 1 || gold_route_phase == 3) {
                        int local_tick = (int)gold_route_tick - (int)(enemies[i].motion * GOLD_LOOP_PLANE_DELAY);

                        if (local_tick < 0) {
                            enemies[i].dx = 3;
                            enemies[i].dy = 0;
                        } else if (local_tick < GOLD_LOOP_TICKS) {
                            set_gold_loop_motion(&enemies[i], (u8)(local_tick / GOLD_LOOP_STAGE_TICKS));
                        } else {
                            enemies[i].dx = 3;
                            enemies[i].dy = 0;
                        }

                        enemies[i].x += enemies[i].dx;
                        enemies[i].y += enemies[i].dy;
                    } else {
                        enemies[i].dx = gold_dx;
                        enemies[i].dy = gold_dy;
                        if (gold_route_phase == 0) {
                            enemies[i].x = gold_base_x - (enemies[i].motion * GOLD_SPACING);
                            enemies[i].y = gold_base_y;
                        } else {
                            enemies[i].x += enemies[i].dx;
                            enemies[i].y += enemies[i].dy;
                        }
                    }

                    if (gold_route_phase >= 4 && enemies[i].x > SCREEN_W) {
                        enemies[i].active = 0;
                    }

                    continue;
                }

                coord_t target_y = player_active ? player_y : SCREEN_H / 2;
                u8 side_mode = enemies[i].motion & (ENEMY_SIDE_MODE_VERTICAL | ENEMY_SIDE_MODE_TURN);
                u8 side_ticks = (enemies[i].motion & ENEMY_SIDE_TICK_MASK) >> ENEMY_SIDE_TICK_SHIFT;

                if (side_mode == 0 && enemies[i].dx != 0 && enemies[i].dy == 0 &&
                    enemies[i].x > 40 && enemies[i].x < SCREEN_W - 40) {
                    u8 side_choice = next_random();

                    if ((side_choice & 0x3F) == 0) {
                        enemies[i].motion = (enemies[i].dx > 0 ? ENEMY_SIDE_DIR_RIGHT : 0) |
                                            ENEMY_SIDE_MODE_TURN_TO_VERTICAL |
                                            (ENEMY_SIDE_TURN_TICKS << ENEMY_SIDE_TICK_SHIFT);
                        enemies[i].dx = ENEMY_SIDE_TURN_STEP(enemies[i].motion & ENEMY_SIDE_DIR_RIGHT);

                        if (enemies[i].y < 72) {
                            enemies[i].dy = 1;
                        } else if (enemies[i].y > SCREEN_H - 72) {
                            enemies[i].dy = -1;
                        } else if ((next_random() & 0x01) == 0) {
                            enemies[i].dy = target_y < enemies[i].y ? -1 : 1;
                        } else {
                            enemies[i].dy = (next_random() & 0x01) ? 1 : -1;
                        }
                    }
                }

                side_mode = enemies[i].motion & (ENEMY_SIDE_MODE_VERTICAL | ENEMY_SIDE_MODE_TURN);
                side_ticks = (enemies[i].motion & ENEMY_SIDE_TICK_MASK) >> ENEMY_SIDE_TICK_SHIFT;

                if (side_mode == ENEMY_SIDE_MODE_VERTICAL) {
                    if (side_ticks != 0) {
                        enemies[i].motion = (enemies[i].motion & (ENEMY_SIDE_DIR_RIGHT | ENEMY_SIDE_MODE_VERTICAL)) |
                                            ((side_ticks - 1U) << ENEMY_SIDE_TICK_SHIFT);
                    } else {
                        u8 next_dir = (next_random() & 0x03) == 0 ? (enemies[i].motion ^ ENEMY_SIDE_DIR_RIGHT) & ENEMY_SIDE_DIR_RIGHT :
                                      enemies[i].motion & ENEMY_SIDE_DIR_RIGHT;
                        enemies[i].motion = next_dir |
                                            ENEMY_SIDE_MODE_TURN_TO_HORIZONTAL |
                                            (ENEMY_SIDE_TURN_TICKS << ENEMY_SIDE_TICK_SHIFT);
                        enemies[i].dx = ENEMY_SIDE_TURN_STEP(next_dir);
                        enemies[i].dy = enemies[i].dy > 0 ? 1 : -1;
                    }
                } else if (side_mode == ENEMY_SIDE_MODE_TURN_TO_VERTICAL) {
                    if (side_ticks != 0) {
                        enemies[i].motion = (enemies[i].motion & (ENEMY_SIDE_DIR_RIGHT | ENEMY_SIDE_MODE_TURN_TO_VERTICAL)) |
                                            ((side_ticks - 1U) << ENEMY_SIDE_TICK_SHIFT);
                    } else {
                        u8 vertical_ticks = ENEMY_SIDE_VERTICAL_MIN_TICKS + (next_random() & 0x07);
                        enemies[i].dx = 0;
                        enemies[i].dy = enemies[i].dy > 0 ? ENEMY_SIDE_SPEED : -ENEMY_SIDE_SPEED;
                        enemies[i].motion = (enemies[i].motion & ENEMY_SIDE_DIR_RIGHT) |
                                            ENEMY_SIDE_MODE_VERTICAL |
                                            (u8)(vertical_ticks << ENEMY_SIDE_TICK_SHIFT);
                    }
                } else if (side_mode == ENEMY_SIDE_MODE_TURN_TO_HORIZONTAL) {
                    if (side_ticks != 0) {
                        enemies[i].motion = (enemies[i].motion & (ENEMY_SIDE_DIR_RIGHT | ENEMY_SIDE_MODE_TURN_TO_HORIZONTAL)) |
                                            ((side_ticks - 1U) << ENEMY_SIDE_TICK_SHIFT);
                    } else {
                        enemies[i].dx = enemy_side_saved_dx(&enemies[i]);
                        enemies[i].dy = 0;
                        enemies[i].motion &= ENEMY_SIDE_DIR_RIGHT;
                    }
                }

                enemies[i].x += enemies[i].dx;
                enemies[i].y += enemies[i].dy;

                side_mode = enemies[i].motion & (ENEMY_SIDE_MODE_VERTICAL | ENEMY_SIDE_MODE_TURN);
                if (side_mode == 0 && enemies[i].dy != 0) {
                    if (enemies[i].x > 32 && enemies[i].x < SCREEN_W - 32) {
                        if ((next_random() & 0x7F) == 0) {
                            enemies[i].dx = -enemies[i].dx;
                            enemies[i].motion ^= ENEMY_SIDE_DIR_RIGHT;
                        } else if ((next_random() & 0x3F) == 0) {
                            enemies[i].dx = enemy_side_saved_dx(&enemies[i]);
                            enemies[i].dy = 0;
                        } else if ((next_random() & 0x7F) == 0) {
                            enemies[i].dx = 0;
                            enemies[i].dy = enemies[i].dy > 0 ? ENEMY_SIDE_SPEED : -ENEMY_SIDE_SPEED;
                            enemies[i].motion = (enemies[i].motion & ENEMY_SIDE_DIR_RIGHT) |
                                                ENEMY_SIDE_MODE_VERTICAL |
                                                ((ENEMY_SIDE_VERTICAL_MIN_TICKS + 4U) << ENEMY_SIDE_TICK_SHIFT);
                        }
                    }

                    if (enemies[i].y < PLAYER_BOUND_TOP) {
                        enemies[i].dy = ENEMY_SIDE_DIAG_DY;
                    } else if (enemies[i].y > SCREEN_H - PLAYER_BOUND_BOTTOM - ENEMY_H) {
                        enemies[i].dy = -ENEMY_SIDE_DIAG_DY;
                    }

                    if (enemies[i].y < -ENEMY_H || enemies[i].y > SCREEN_H) {
                        enemies[i].active = 0;
                    }
                } else if (enemies[i].y < PLAYER_BOUND_TOP) {
                    enemies[i].y = PLAYER_BOUND_TOP;
                    enemies[i].dy = side_mode == ENEMY_SIDE_MODE_VERTICAL ? ENEMY_SIDE_SPEED :
                                    (side_mode & ENEMY_SIDE_MODE_TURN) ? 1 : 0;
                } else if (enemies[i].y > SCREEN_H - PLAYER_BOUND_BOTTOM - ENEMY_H) {
                    enemies[i].y = SCREEN_H - PLAYER_BOUND_BOTTOM - ENEMY_H;
                    enemies[i].dy = side_mode == ENEMY_SIDE_MODE_VERTICAL ? -ENEMY_SIDE_SPEED :
                                    (side_mode & ENEMY_SIDE_MODE_TURN) ? -1 : 0;
                }

                if (enemies[i].x < -ENEMY_W || enemies[i].x > SCREEN_W) {
                    enemies[i].active = 0;
                }

                if (enemies[i].x > 0 && enemies[i].x < SCREEN_W - ENEMY_W &&
                    enemies[i].y > PLAYER_BOUND_TOP && enemies[i].y < SCREEN_H - PLAYER_BOUND_BOTTOM &&
                    (next_random() & 0x7F) == 0) {
                    fire_green_enemy_bullet(&enemies[i]);
                }

                continue;
            }

            u8 pattern = enemies[i].motion & ENEMY_PATTERN_MASK;
            u8 kind = (enemies[i].motion >> ENEMY_ANIM_KIND_SHIFT) & 0x03;

            if (kind == 0 && pattern == 3 && enemies[i].y >= SCREEN_H / 2 && enemies[i].dx == 0) {
                if ((next_random() & 0x03) == 0) {
                    enemies[i].dx = player_x < enemies[i].x ? -ENEMY_DRIFT_SPEED : ENEMY_DRIFT_SPEED;
                    enemies[i].motion = 3U << ENEMY_ANIM_KIND_SHIFT;
                } else {
                    enemies[i].motion = 0;
                }
            } else if (kind == 0 && pattern == 5 && enemies[i].y >= SCREEN_H / 2 && enemies[i].dx == 0) {
                if ((next_random() & 0x03) == 0) {
                    enemies[i].dx = player_x < enemies[i].x ? -ENEMY_DRIFT_SPEED : ENEMY_DRIFT_SPEED;
                    enemies[i].motion = 3U << ENEMY_ANIM_KIND_SHIFT;
                } else {
                    enemies[i].motion = 0;
                }
            } else if (kind == 0 && pattern == 4 && enemies[i].y >= SCREEN_H / 2 && enemies[i].dx == 0) {
                if ((next_random() & 0x03) == 0) {
                    enemies[i].dx = player_x < enemies[i].x ? -ENEMY_DRIFT_SPEED : ENEMY_DRIFT_SPEED;
                    enemies[i].motion = 0 | (3U << ENEMY_ANIM_KIND_SHIFT);
                } else {
                    enemies[i].motion = 0;
                }
            } else if (kind == 0 && (pattern == 1 || pattern == 2) && enemies[i].y >= SCREEN_H / 2 && enemies[i].dx != 0) {
                if ((next_random() & 0x03) == 0) {
                    enemies[i].dx = 0;
                    enemies[i].dy = 0;
                    enemies[i].motion = (pattern == 1 ? 6U : 7U) | (1U << ENEMY_ANIM_KIND_SHIFT);
                } else {
                    enemies[i].motion = 0;
                }
            }

            kind = (enemies[i].motion >> ENEMY_ANIM_KIND_SHIFT) & 0x03;
            u8 frame = enemies[i].motion >> ENEMY_ANIM_FRAME_SHIFT;
            if (kind != 0 && frame < ENEMY_ANIM_FRAMES - 1) {
                enemies[i].motion += 1U << ENEMY_ANIM_FRAME_SHIFT;
            } else if (kind == 1) {
                pattern = enemies[i].motion & ENEMY_PATTERN_MASK;
                enemies[i].dx = pattern == 6 ? -ENEMY_DRIFT_SPEED : ENEMY_DRIFT_SPEED;
                enemies[i].dy = -ENEMY_REVERSE_SPEED;
                enemies[i].motion = pattern | (1U << ENEMY_ANIM_KIND_SHIFT) | ((ENEMY_ANIM_FRAMES - 1U) << ENEMY_ANIM_FRAME_SHIFT);
            } else if (kind == 2) {
                enemies[i].dx = 0;
                enemies[i].dy = ENEMY_SPEED;
                enemies[i].motion = 0;
            }

            kind = (enemies[i].motion >> ENEMY_ANIM_KIND_SHIFT) & 0x03;
            frame = enemies[i].motion >> ENEMY_ANIM_FRAME_SHIFT;
            if (kind == 1 && frame == ENEMY_ANIM_FRAMES - 1 && enemies[i].dy < 0 && (next_random() & 0x1F) == 0) {
                enemies[i].dy = 0;
                enemies[i].motion = (enemies[i].motion & ENEMY_PATTERN_MASK) | (2U << ENEMY_ANIM_KIND_SHIFT);
            }

            enemies[i].x += enemies[i].dx;
            enemies[i].y += enemies[i].dy;

            if (enemies[i].y > 48 && enemies[i].y < 200 && (next_random() & 0x7F) == 0) {
                fire_enemy_bullet(&enemies[i]);
            }

            if (enemies[i].y > SCREEN_H || enemies[i].y < -ENEMY_H || enemies[i].x < -ENEMY_W || enemies[i].x > SCREEN_W) {
                enemies[i].active = 0;
            }
        }
    }
}

static void handle_player_bullet_enemy_collisions(void)
{
    for (int b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if (player_bullets[b].active != 1) {
            continue;
        }

        for (int e = 0; e < MAX_ENEMIES; e++) {
            if (!enemies[e].active || enemies[e].life == 0) {
                continue;
            }

            if (enemy_bullet_overlap(&enemies[e], &player_bullets[b])) {
                shots_hit++;
                total_shots_hit++;
                if (enemies[e].type == ENEMY_TYPE_BOSS || enemies[e].type == ENEMY_TYPE_MEDIUM) {
                    player_bullets[b].active = 2;
                    player_bullets[b].explosion_frame = 0;
                    if (enemies[e].life > 1) {
                        enemies[e].life--;
                        break;
                    }
                } else {
                    player_bullets[b].active = 0;
                }

                add_score(enemy_point_value(enemies[e].type));

                if (enemies[e].type == ENEMY_TYPE_GOLD && gold_formation_alive != 0) {
                    gold_formation_alive--;
                    if (gold_formation_alive == 0) {
                        add_score(POINTS_GOLD_CLEAR);
                        show_gold_bonus_at(enemies[e].x, enemies[e].y);
                    }
                }
                enemies[e].life = 0;
                enemies[e].explosion_frame = 0;
                enemies_killed++;
                if (enemies[e].type == ENEMY_TYPE_BOSS) {
                    boss_exit_active = 0;
                    boss_flight_ticks = 0;
                    boss_burst_remaining = 0;
                    boss_burst_gap = 0;
                    boss_burst_cooldown = BOSS_BURST_COOLDOWN;
                }

                break;
            }
        }
    }
}

static void handle_player_hit_collisions(void)
{
    if (!player_active || player_is_exploding() || player_is_rolling()) {
        return;
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (enemy_bullets[i].active && player_bullet_overlap(&enemy_bullets[i])) {
            enemy_bullets[i].active = 0;
            start_player_explosion();
            return;
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].life != 0 && player_enemy_overlap(&enemies[i])) {
            if (enemies[i].type == ENEMY_TYPE_GOLD && gold_formation_alive != 0) {
                gold_formation_alive--;
                if (gold_formation_alive == 0) {
                    show_gold_bonus_at(enemies[i].x, enemies[i].y);
                }
            }

            enemies[i].life = 0;
            enemies[i].explosion_frame = 0;
            if (enemies[i].type == ENEMY_TYPE_BOSS) {
                boss_exit_active = 0;
                boss_flight_ticks = 0;
                boss_burst_remaining = 0;
                boss_burst_gap = 0;
                boss_burst_cooldown = BOSS_BURST_COOLDOWN;
            }

            start_player_explosion();
            return;
        }
    }
}

static u32 pack_oam_entry(u8 y, u8 tile_index, u8 attributes, u8 x)
{
    return ((u32)x << 24) |
           ((u32)attributes << 16) |
           ((u32)tile_index << 8) |
           (u32)y;
}

static u8 make_oam_attributes(u8 palette, int behind_background, int flip_h, int flip_v)
{
    u8 attributes = palette & OAM_ATTR_PALETTE_MASK;

    if (behind_background) {
        attributes |= OAM_ATTR_PRIORITY;
    }

    if (flip_h) {
        attributes |= OAM_ATTR_FLIP_H;
    }

    if (flip_v) {
        attributes |= OAM_ATTR_FLIP_V;
    }

    return attributes;
}

static void write_oam_entry(u32 sprite_index, u8 y, u8 tile_index, u8 attributes, u8 x)
{
    HDMI_TEXT_CONTROLLER_mWriteReg(
        XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR,
        HDMI_TEXT_CONTROLLER_REG_OFFSET(OAM_BASE_REG + sprite_index),
        pack_oam_entry(y, tile_index, attributes, x));
}

static void clear_oam_entry(u32 sprite_index)
{
    HDMI_TEXT_CONTROLLER_mWriteReg(
        XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR,
        HDMI_TEXT_CONTROLLER_REG_OFFSET(OAM_BASE_REG + sprite_index),
        0U);
}

static void write_game_reg(u32 reg_index, u32 value)
{
    HDMI_TEXT_CONTROLLER_mWriteReg(
        XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR,
        HDMI_TEXT_CONTROLLER_REG_OFFSET(GAME_REG_BASE + reg_index),
        value);
}

static u32 read_game_reg(u32 reg_index)
{
    return HDMI_TEXT_CONTROLLER_mReadReg(
        XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR,
        HDMI_TEXT_CONTROLLER_REG_OFFSET(GAME_REG_BASE + reg_index));
}

static void write_digits_to_hardware(u32 base_oam, u8 digits, u8 x, u8 y, u32 value)
{
    for (int i = digits - 1; i >= 0; i--) {
        u8 digit = (u8)(value % 10U);

        write_oam_entry(
            base_oam + (u32)i,
            y,
            TILE_DIGIT(digit),
            make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
            x + (u8)(i * 8));

        value /= 10U;
    }
}

static void write_revealed_digits_to_hardware(u32 base_oam, u8 digits, u8 visible_digits, u8 x, u8 y, u32 value)
{
    u32 divisor = 1U;

    for (u8 i = 1; i < digits; i++) {
        divisor *= 10U;
    }

    for (u8 i = 0; i < digits; i++) {
        if (i < visible_digits) {
            u8 digit = (u8)((value / divisor) % 10U);

            write_oam_entry(
                base_oam + (u32)i,
                y,
                TILE_DIGIT(digit),
                make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
                x + (u8)(i * 8));
        } else {
            clear_oam_entry(base_oam + (u32)i);
        }

        divisor /= 10U;
    }
}

static void write_score_to_hardware(u8 x, u8 y)
{
    write_digits_to_hardware(OAM_SCORE_BASE, SCORE_DIGITS, x, y, score);
}

static void write_congrats_to_hardware(void)
{
    static const u8 tiles[CONGRATS_CHARS] = {90, 103, 102, 95, 105, 88, 107, 108, 100, 88, 107, 97, 103, 102, 106};

    for (u8 i = 0; i < CONGRATS_CHARS; i++) {
        if (i < congrats_visible_chars) {
            write_oam_entry(
                OAM_CONGRATS_BASE + (u32)i,
                CONGRATS_Y,
                tiles[i],
                make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
                CONGRATS_X + (u8)(i * 8));
        } else {
            clear_oam_entry(OAM_CONGRATS_BASE + (u32)i);
        }
    }
}

static void clear_overlay_digits(void)
{
    clear_oam_entry(OAM_LIVES_TENS);
    clear_oam_entry(OAM_LIVES_ONES);
    clear_oam_entry(OAM_LEVEL_TENS);
    clear_oam_entry(OAM_LEVEL_ONES);
    clear_oam_entry(OAM_PLAYER_NUMBER);

    for (int i = 0; i < 4; i++) {
        clear_oam_entry(OAM_ROLL_BONUS_BASE + (u32)i);
    }

    for (int i = 0; i < 2; i++) {
        clear_oam_entry(OAM_ACCURACY_PERCENT_BASE + (u32)i);
    }

    for (int i = 0; i < 4; i++) {
        clear_oam_entry(OAM_ACCURACY_BONUS_BASE + (u32)i);
    }

    for (int i = 0; i < SCORE_DIGITS; i++) {
        clear_oam_entry(OAM_HIGH_SCORE_BASE + (u32)i);
    }

    for (int i = 0; i < 5; i++) {
        clear_oam_entry(OAM_KILLS_BASE + (u32)i);
    }

    for (int i = 0; i < 3; i++) {
        clear_oam_entry(OAM_DEATH_ACCURACY_BASE + (u32)i);
    }

    for (int i = 0; i < CONGRATS_CHARS; i++) {
        clear_oam_entry(OAM_CONGRATS_BASE + (u32)i);
    }
}

static void write_fixed_digits(u32 base_oam, u8 digits, u8 x, u8 y, u32 value)
{
    write_digits_to_hardware(base_oam, digits, x, y, value);
}

static void write_overlay_digits(u32 flags)
{
    u8 visible_lives = player_lives == 0 ? 0 : player_lives - 1U;
    u8 visible_level = current_level + 1U;
    u8 attrs = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);

    for (int i = 0; i < SCORE_DIGITS; i++) {
        clear_oam_entry(OAM_HIGH_SCORE_BASE + (u32)i);
    }
    for (int i = 0; i < 5; i++) {
        clear_oam_entry(OAM_KILLS_BASE + (u32)i);
    }
    for (int i = 0; i < 3; i++) {
        clear_oam_entry(OAM_DEATH_ACCURACY_BASE + (u32)i);
    }

    if (flags & GAME_FLAG_INTRO_OVERLAY) {
        write_oam_entry(OAM_LIVES_TENS, OVERLAY_LIVES_Y, TILE_DIGIT(0), attrs, OVERLAY_LIVES_X);
        write_oam_entry(OAM_LIVES_ONES, OVERLAY_LIVES_Y, TILE_DIGIT(visible_lives), attrs, OVERLAY_LIVES_X + 8);
        write_oam_entry(OAM_PLAYER_NUMBER, OVERLAY_PLAYER_Y, TILE_DIGIT(active_player + 1U), attrs, OVERLAY_PLAYER_X);
        write_oam_entry(OAM_LEVEL_TENS, OVERLAY_LEVEL_Y, TILE_DIGIT(0), attrs, OVERLAY_LEVEL_X);
        write_oam_entry(OAM_LEVEL_ONES, OVERLAY_LEVEL_Y, TILE_DIGIT(visible_level), attrs, OVERLAY_LEVEL_X + 8);
        for (int i = 0; i < 4; i++) {
            clear_oam_entry(OAM_ROLL_BONUS_BASE + (u32)i);
            clear_oam_entry(OAM_ACCURACY_BONUS_BASE + (u32)i);
        }
        for (int i = 0; i < 2; i++) {
            clear_oam_entry(OAM_ACCURACY_PERCENT_BASE + (u32)i);
        }
    } else {
        clear_oam_entry(OAM_LIVES_TENS);
        clear_oam_entry(OAM_LIVES_ONES);
        clear_oam_entry(OAM_LEVEL_TENS);
        clear_oam_entry(OAM_LEVEL_ONES);
        clear_oam_entry(OAM_PLAYER_NUMBER);
        write_fixed_digits(OAM_ROLL_BONUS_BASE, 4, STATS_ROLL_BONUS_X, STATS_ROLL_BONUS_Y, stats_roll_bonus);
        write_fixed_digits(OAM_ACCURACY_PERCENT_BASE, 2, STATS_ACCURACY_X, STATS_ACCURACY_Y, stats_accuracy_percent);
        write_fixed_digits(OAM_ACCURACY_BONUS_BASE, 4, STATS_ACCURACY_BONUS_X, STATS_ACCURACY_BONUS_Y, stats_accuracy_bonus);
    }
}

static u8 boss_death_tile(u8 frame)
{
    static const u8 tiles[] = {38, 27, 64, 56, 57, 58, 59, 58, 64, 57, 60, 61, 62, 63, 72};
    u8 index = frame >> 2U;

    if (index >= sizeof(tiles)) {
        index = sizeof(tiles) - 1U;
    }

    return tiles[index];
}

static u8 medium_death_tile(u8 frame)
{
    static const u8 tiles[] = {64, 56, 57, 58, 64, 59, 60, 61, 62, 63, 91};
    u8 index = frame >> 2U;

    if (index >= sizeof(tiles)) {
        index = sizeof(tiles) - 1U;
    }

    return tiles[index];
}

static void write_sprites_to_hardware(void)
{
    if (congrats_active && congrats_start_delay == 0) {
        clear_oam_entry(OAM_PLAYER_SPRITE);

        for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
            clear_oam_entry(OAM_BULLET_BASE + i);
        }

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
            clear_oam_entry(OAM_ENEMY_BULLET_BASE + i);
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            clear_oam_entry(OAM_ENEMY_BASE + i);
        }

        clear_oam_entry(OAM_POWERUP);
        clear_oam_entry(OAM_GOLD_BONUS);
        clear_oam_entry(OAM_ROLL_COUNT);
        clear_oam_entry(OAM_START_ICON);
        clear_overlay_digits();
        write_congrats_to_hardware();
        return;
    }

    if (start_screen_active || game_over_active) {
        clear_oam_entry(OAM_PLAYER_SPRITE);

        for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
            clear_oam_entry(OAM_BULLET_BASE + i);
        }

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
            clear_oam_entry(OAM_ENEMY_BULLET_BASE + i);
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            clear_oam_entry(OAM_ENEMY_BASE + i);
        }

        clear_oam_entry(OAM_POWERUP);
        clear_oam_entry(OAM_GOLD_BONUS);
        clear_oam_entry(OAM_ROLL_COUNT);
        clear_overlay_digits();

        write_score_to_hardware(SCORE_X, SCORE_Y);
        write_digits_to_hardware(OAM_HIGH_SCORE_BASE, SCORE_DIGITS, HIGH_SCORE_X, HIGH_SCORE_Y, high_score);

        if (game_over_active) {
            write_revealed_digits_to_hardware(OAM_KILLS_BASE, 5, game_over_kill_digits, KILLS_X, KILLS_Y, enemies_killed);
            write_revealed_digits_to_hardware(
                OAM_DEATH_ACCURACY_BASE,
                3,
                game_over_accuracy_digits,
                DEATH_ACCURACY_X,
                DEATH_ACCURACY_Y,
                total_accuracy_percent());
            clear_oam_entry(OAM_START_ICON);
            return;
        }

        write_oam_entry(
            OAM_START_ICON,
            start_selection_bottom ? START_ICON_BOTTOM_Y : START_ICON_TOP_Y,
            TILE_START_ICON,
            make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
            START_ICON_X);
        return;
    }

    clear_oam_entry(OAM_START_ICON);

    if (player_active || player_is_exploding()) {
        write_oam_entry(
            OAM_PLAYER_SPRITE,
            (u8)player_y,
            player_tile(),
            make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
            (u8)player_x);
    } else {
        clear_oam_entry(OAM_PLAYER_SPRITE);
    }

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        if (player_bullets[i].active && player_bullets[i].y >= 0) {
            u8 player_bullet_tile = power_bullets_active ? TILE_PLAYER_BULLET_POWER : TILE_PLAYER_BULLET;

            if (player_bullets[i].active == 2) {
                player_bullet_tile = player_bullets[i].explosion_frame < 2 ? TILE_EXPLOSION_0 : TILE_EXPLOSION_1;
            }

            write_oam_entry(
                OAM_BULLET_BASE + i,
                (u8)player_bullets[i].y,
                player_bullet_tile,
                make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
                (u8)player_bullets[i].x);
        } else {
            clear_oam_entry(OAM_BULLET_BASE + i);
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (enemy_bullets[i].active && enemy_bullets[i].y >= 0) {
            write_oam_entry(
                OAM_ENEMY_BULLET_BASE + i,
                (u8)enemy_bullets[i].y,
                TILE_ENEMY_BULLET,
                make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
                (u8)enemy_bullets[i].x);
        } else {
            clear_oam_entry(OAM_ENEMY_BULLET_BASE + i);
        }
    }

    if (powerup.active && powerup.y >= 0 && powerup.y < SCREEN_H) {
        write_oam_entry(
            OAM_POWERUP,
            (u8)powerup.y,
            TILE_POWERUP,
            make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
            (u8)powerup.x);
    } else {
        clear_oam_entry(OAM_POWERUP);
    }

    if (gold_bonus_ticks != 0 && gold_bonus_y >= 0 && gold_bonus_y < SCREEN_H) {
        write_oam_entry(
            OAM_GOLD_BONUS,
            (u8)gold_bonus_y,
            gold_bonus_tile,
            make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
            (u8)gold_bonus_x);
    } else {
        clear_oam_entry(OAM_GOLD_BONUS);
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].y >= 0 && enemies[i].y < SCREEN_H && enemies[i].x < SCREEN_W &&
            (enemies[i].x >= 0 ||
             ((enemies[i].type == ENEMY_TYPE_SIDE || enemies[i].type == ENEMY_TYPE_GOLD) && enemies[i].x > -ENEMY_W) ||
             (enemies[i].type == ENEMY_TYPE_MEDIUM && enemies[i].x > -MEDIUM_W))) {
            u8 enemy_tile;
            u8 enemy_attributes;

            if (enemies[i].life == 0 && enemies[i].type == ENEMY_TYPE_BOSS) {
                enemy_tile = boss_death_tile(enemies[i].explosion_frame);
                enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);
            } else if (enemies[i].life == 0 && enemies[i].type == ENEMY_TYPE_MEDIUM) {
                enemy_tile = medium_death_tile(enemies[i].explosion_frame);
                enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);
            } else if (enemies[i].life == 0) {
                enemy_tile = TILE_EXPLOSION(enemies[i].explosion_frame);
                enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);
            } else if (enemies[i].type == ENEMY_TYPE_BOSS) {
                enemy_tile = TILE_BOSS_GREEN;
                enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);
            } else if (enemies[i].type == ENEMY_TYPE_MEDIUM) {
                enemy_tile = enemy_medium_tile(&enemies[i]);
                enemy_attributes = enemy_medium_attributes(&enemies[i]);
            } else if (enemies[i].type == ENEMY_TYPE_SIDE || enemies[i].type == ENEMY_TYPE_GOLD) {
                enemy_tile = enemy_side_tile(&enemies[i]);
                if (enemies[i].type == ENEMY_TYPE_SIDE) {
                    enemy_attributes = enemy_side_attributes(&enemies[i]);
                } else {
                    enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, enemies[i].dx < 0, enemies[i].dx == 0 ? enemies[i].dy > 0 : enemies[i].dy < 0);
                }
            } else {
                enemy_tile = enemy_plane_tile(&enemies[i]);
                enemy_attributes = make_oam_attributes(OAM_PALETTE_0, 0, 0, 0);
            }
            if ((enemies[i].type == ENEMY_TYPE_SIDE || enemies[i].type == ENEMY_TYPE_GOLD) && enemies[i].x < 0) {
                enemy_attributes |= OAM_ATTR_PRIORITY;
            }

            write_oam_entry(
                OAM_ENEMY_BASE + i,
                (u8)enemies[i].y,
                enemy_tile,
                enemy_attributes,
                (u8)enemies[i].x);
        } else {
            clear_oam_entry(OAM_ENEMY_BASE + i);
        }
    }

    {
        u32 flags = read_game_reg(GAME_REG_FLAGS);
        int intro_overlay = (flags & GAME_FLAG_INTRO_OVERLAY) != 0;
        int stats_overlay = (flags & GAME_FLAG_STATS_OVERLAY) != 0;
        int gameplay_roll_visible = !player_is_launching() && !player_is_landing() &&
                                    !player_is_exploding() && player_respawn_timer == 0;

        if (intro_overlay || stats_overlay) {
            write_overlay_digits(flags);
        } else {
            clear_overlay_digits();
        }

        if (intro_overlay || stats_overlay || gameplay_roll_visible) {
            write_oam_entry(
                OAM_ROLL_COUNT,
                ROLL_COUNT_Y,
                TILE_DIGIT(player_rolls_available),
                make_oam_attributes(OAM_PALETTE_0, 0, 0, 0),
                ROLL_COUNT_X);
        } else {
            clear_oam_entry(OAM_ROLL_COUNT);
        }
    }

    write_score_to_hardware(active_player == 0 ? GAMEPLAY_SCORE_X : GAMEPLAY_P2_SCORE_X, GAMEPLAY_SCORE_Y);
}

static u32 get_usb_ticks(void)
{
    return XTmrCtr_GetValue(&Usb_timer, 0);
}

int main(void)
{
    BYTE rcode;
    BYTE device = 0xFF;
    BYTE runningdebugflag = 0;
    BOOT_KBD_REPORT kbdbuf;
    BOOT_KBD_REPORT active_kbd = {0};
    BYTE have_keyboard_report = 0;
    u32 last_move_ticks = 0;
    u32 last_kbd_poll_ticks = 0;
    u32 last_usb_service_ticks = 0;

    init_platform();
    reset_game_state();
    write_game_reg(GAME_REG_FLAGS, GAME_FLAG_START_SCREEN);
    write_sprites_to_hardware();

    MAX3421E_init();

    USB_init();
    random_state ^= (u8)get_usb_ticks();
    random_state |= 1U;

    while (1) {
        u32 now_ticks = get_usb_ticks();
        if ((u32)(now_ticks - last_move_ticks) >= PLAYER_MOVE_PERIOD_TICKS) {
            last_move_ticks = now_ticks;

            update_player_explosion();

            if (congrats_active) {
                update_congrats_screen();
                write_sprites_to_hardware();
                continue;
            }

            if (game_over_active) {
                update_game_over_screen();
                write_sprites_to_hardware();
                continue;
            }

            if (start_screen_active) {
                update_start_screen(&active_kbd, have_keyboard_report);
                write_sprites_to_hardware();
                continue;
            }

            if (player_is_launching()) {
                update_player_launch();
                write_sprites_to_hardware();
                continue;
            }

            if (player_is_landing()) {
                update_player_landing();
                update_landing_enemy_explosions();
                write_sprites_to_hardware();
                continue;
            }

            if (have_keyboard_report && player_active && !player_is_exploding()) {
                u8 x_down = key_is_down(&active_kbd, KEY_X);

                if (x_down && !roll_x_was_down) {
                    start_player_roll();
                }
                roll_x_was_down = x_down;

                if (player_is_rolling()) {
                    update_player_x_from_keyboard(&active_kbd);
                } else {
                    update_player_from_keyboard(&active_kbd);
                }
            } else {
                roll_x_was_down = 0;
            }

            if (have_keyboard_report && player_active && !player_is_exploding() &&
                !player_is_rolling() && key_is_down(&active_kbd, KEY_Z)) {
                fire_player_bullet(now_ticks);
            }

            update_player_roll();
            update_player_bullets();
            update_enemy_bullets();
            update_powerup();
            update_enemies(now_ticks);
            handle_player_bullet_enemy_collisions();
            handle_player_hit_collisions();
            update_level_progress();
            update_player_respawn();
            write_sprites_to_hardware();
        }

        if ((GetUsbTaskState() != USB_STATE_RUNNING) &&
            ((u32)(now_ticks - last_usb_service_ticks) >= USB_ENUM_SERVICE_PERIOD_TICKS)) {
            last_usb_service_ticks = now_ticks;
            MAX3421E_Task();
            USB_Task();
        }

        if (GetUsbTaskState() == USB_STATE_RUNNING) {
            if (!runningdebugflag) {
                runningdebugflag = 1;
                device = GetDriverandReport();
            } else if (device == HID_KEYBOARD) {
                if ((u32)(now_ticks - last_kbd_poll_ticks) < KBD_POLL_PERIOD_TICKS) {
                    continue;
                }

                last_kbd_poll_ticks = now_ticks;
                rcode = kbdPoll(&kbdbuf);

                if (rcode == 0) {
                    if (!have_keyboard_report) {
                        random_state ^= (u8)now_ticks;
                        random_state |= 1U;
                    }
                    active_kbd = kbdbuf;
                    have_keyboard_report = 1;
                } else if (rcode != hrNAK) {
                    have_keyboard_report = 0;
                    active_kbd = (BOOT_KBD_REPORT){0};
                }
            }
        } else {
            if (runningdebugflag) {
                runningdebugflag = 0;
                device = 0xFF;
                have_keyboard_report = 0;
                active_kbd = (BOOT_KBD_REPORT){0};
            }
        }
    }

    cleanup_platform();
    return 0;
}
