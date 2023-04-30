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
#include <osgParticle/Counter>
#include <osgParticle/ConstantRateCounter>
#include <osgParticle/Program>
#include <osgParticle/ExplosionOperator>


class CExplosion
{
public:
	CExplosion(void);
	~CExplosion(void);
public:
	//������ըЧ��
	virtual void createExplosion(osg::ref_ptr<osg::MatrixTransform> explosion);
	//������ը��Ƭ
	virtual void createExplosionDebris( osg::ref_ptr<osg::MatrixTransform> explosionDebris, 
		char* texture, 
		float life, 
		float minSize, 
		float maxSize, 
		float minNum, 
		float maxNum, 
		float minSpeed, 
		float maxSpeed );
	// 	//�Ž���ϸС��
// 	virtual void createExplosionFire(osg::ref_ptr<osg::MatrixTransform> explosionFire);
// 	//������ֵĻ��
// 	virtual void createExplosionGroundLight(osg::ref_ptr<osg::MatrixTransform> explosionGroundLight);
protected:
		
};
