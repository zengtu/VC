#pragma once

#include <osg/ref_ptr>
#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/Geode>
#include <osgParticle/Particle>
#include <osgParticle/PointPlacer>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/RadialShooter>
#include <osgParticle/AccelOperator>
#include <osgParticle/FluidFrictionOperator>
#include <osgParticle/LinearInterpolator>
#include <osgParticle/BoxPlacer>


class CFire
{
public:
	CFire(void);
	~CFire(void);
public:
	virtual void createFireBall(osg::ref_ptr<osg::MatrixTransform> smokeNode);
};
