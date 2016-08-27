#pragma once
#include "Obstacle.h"
#include "cinder/gl/Material.h"


namespace ar {
	class ObstaclePopArea : public ar::GameObject {
	public:

		// 湧き位置 範囲 機雷の半径 個数
		ObstaclePopArea(const ci::Vec3f& position_,
						float pop_range_,
						float radius_,
						int count_);
		ObstaclePopArea() {}

		void update()override;
		void draw()override;
		void transDraw()override;

		std::list<Obstacle> getObstacles() {
			return obstacles;
		}

		// 一番近い障害物を返す
		Obstacle getNearestObstacle(ci::Vec3f target_);

		// 当たったかどうか
		bool isHitObstacle(ci::Vec3f target_, float radius_);

		float getPopRange() {
			return pop_range;
		}

	private:

		std::list<Obstacle> obstacles;

		// 湧き範囲直径
		float pop_range;

		void obstaclePop(float radius_, int count_);


	private:// デバッグ用の範囲
		void testObstaclePopArea();
		ci::gl::Material test_mt;

	};
}