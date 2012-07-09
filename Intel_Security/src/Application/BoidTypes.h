#ifndef ROXLU_BOID_TYPESH
#define ROXLU_BOID_TYPESH

#include <deque>
#include <pbd/PBD.h>
#include <application/Settings.h>
#include <application/visuals/Trail.h>
#include <roxlu/math/Vec2.h>

enum BoidMode {
	 B_MODE_DEFAULT // all forces are added
	,B_MODE_ATTACK // flocking is disable.. we're attacking
};
	
template<class T>
struct BoidParticle : public Particle<T> {
	BoidParticle(const T& pos, float m = 1.0);
	void update(const float dt);
	void removeTrail();
	
	Trail3PT trail;
	uint64_t grow_trail_end;
	uint64_t glow_end;
	uint64_t attack_start;
	uint64_t attack_end;
	uint64_t attack_delay;
	int mode;
};


template<class T>
BoidParticle<T>::BoidParticle(const T& pos, float m)
	:Particle<T>(pos, m)
	,grow_trail_end(0)
	,glow_end(0)
	,mode(B_MODE_DEFAULT)
	,attack_start(0)
	,attack_end(0)
	,attack_delay(0)
{
}


template<class T>
void BoidParticle<T>::update(const float dt) {

}

template<class T>
inline void BoidParticle<T>::removeTrail() {
	trail.clear();
}



typedef Particles<Vec3, BoidParticle<Vec3>, Spring<Vec3> >	Boids3;
typedef Particles<Vec2, BoidParticle<Vec2>, Spring<Vec2> >	Boids2;

typedef BoidParticle<Vec2> 	Boid2;
typedef BoidParticle<Vec3> 	Boid3;


// Used by flocking to update 
struct BoidFlockForceAdder {
	void operator()(const Vec3& dir, Boid3& boid) {
		if(boid.mode == B_MODE_DEFAULT) {
			boid.addForce(dir);
		}
		else {	
			boid.addForce(dir * 0.1);
		}
	}
};


//typedef Flocking<Vec2, BoidParticle<Vec2>, BoidFlockForceAdder > BoidFlocking2;
typedef Flocking<Vec3, BoidParticle<Vec3>, BoidFlockForceAdder > BoidFlocking3;

// We used these in the app, so we can switch from 2D to 3D
//typedef Boids2 Boids;
//typedef Boid2 Boid;
//typedef BoidFlocking2 BoidFlocking;

typedef Boids3 Boids;
typedef Boid3 Boid;
typedef BoidFlocking3 BoidFlocking;

#endif