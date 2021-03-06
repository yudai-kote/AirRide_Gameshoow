#pragma once
#include "../GameObject.h"
#include "../../Component/Components/Color.h"
#include "../../../Share/Easing/Easing.h"
#include "../../../Share/Time.h"
#include "../SignPost/SignPostManager.h"
#include "../Obstacle/ObstacleManager.h"
#include "../../../TaskManager/ObjDataManager.h"
#include "../../../TaskManager/TextureManager.h"
#include "../../../TaskManager/SoundManager.h"
#include "../../Component/Components/Material.h"
#include "../../Component/Components/Texture.h"


class CharaBase : public ar::GameObject
{
public:

	CharaBase();
	~CharaBase();

	void init();
	virtual void restart();
	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;


	enum class CharaStatus
	{
		NORMAL,
		ROLL,
		DASH,
		CLASH
	};


	ci::Vec3f getWorldPoisition();

	void setSignPostManager(std::shared_ptr<ar::SignPostManager> signpostmanager) { this->signpostmanager = signpostmanager; }
	ci::Matrix44f getMatrix() const { return matrix; }

	CharaStatus getStatus() { return status; }
	float getDashCount() const { return dash_count; }
	float getCollisionCirclerad() const { return collision_circle_rad; }
	float getSpeed() const { return speed; }
	void setSpeed(const float speed) {

		if (status != CharaStatus::NORMAL)
			return;

		float distance_speed = start_speed - end_speed;

		start_speed = speed + distance_speed;
		end_speed = speed;
		this->speed = speed;
	}
	void setIsStop(const bool &is_stop) { this->is_stop = is_stop; }
	void setPosition(const ci::Vec2f &position) {

		if (status != CharaStatus::NORMAL)
			return;

		start_move_pos = position;
		end_move_pos = position;
		move_count = 0.0f;
	}
	float getClashSpeed() const { return clash_speed; }
	void setClashSpeed(const float &clash_speed) { this->clash_speed = clash_speed; }
	float getIntervalCount() const { return interval_count; }
	void setIntervalTakesTime(const float &interval_takes_time) { this->interval_takes_time = interval_takes_time; }

	bool isAttack() { return dash_count <= 0.3f; }
	bool isAction() { return interval_count == 1.0f; }
	bool isInvincible()
	{
		switch (status)
		{
		case CharaStatus::CLASH:
			return clash_count < 1.0f;
		case CharaStatus::ROLL:
			return roll_count < 1.0f;
		default:
			return false;
		}

		return false;
	}
	bool isCharaDashing() { return status == CharaStatus::DASH; }
	bool isCharaRolling() { return status == CharaStatus::ROLL; }

	void moving(ci::Vec2f);
	bool isRolling(ci::Vec2f);
	bool isAttacking();

	void HitObstacle(const float &clash_speed);

protected:

	void debugCourseOutStop();

	void move();
	void roll();
	virtual void dash();
	void collisionToWindow();
	void clash();
	void updateStageMatrix();
	void interval();

	std::shared_ptr<ar::SignPostManager> signpostmanager;
	ci::Matrix44f matrix;

	ci::Vec3f window_size;

	CharaStatus status;
	float speed;

	float collision_circle_rad;
	float move_count;
	float move_count_takes_time;
	ci::Vec2f start_move_pos;
	ci::Vec2f end_move_pos;

	float max_roll_angle;
	float roll_count;
	float start_roll_angle;
	float end_roll_angle;

	float dash_count;
	float start_speed;
	float end_speed;

	float clash_count;
	float max_clash_count;
	float clash_speed;
	float start_clash_speed;
	float end_clash_speed;

	float interval_count;
	float interval_takes_time;

	bool is_stop;

private:

};


ci::Vec2f QuadOut(float t, ci::Vec2f b, ci::Vec2f e);
float QuadOut(float t, float b, float e);