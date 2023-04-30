#include "StdAfx.h"
#include "Smoke.h"

CSmoke::CSmoke(void)
{
}

CSmoke::~CSmoke(void)
{
}

void CSmoke::createDarkSmoke( osg::ref_ptr<osg::MatrixTransform> smokeNode )
{
	// 创建粒子对象，设置其属性并交由粒子系统使用。
	osgParticle::Particle particleTempalte;

	particleTempalte.setShape(osgParticle::Particle::QUAD);
	particleTempalte.setLifeTime(10);                             // 单位：秒
	particleTempalte.setSizeRange (osgParticle::rangef(3.0f,15.0f));   // 单位：米
	particleTempalte.setAlphaRange(osgParticle::rangef(1,0));
	particleTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(0.0f,0.0f,0.0f,0.0f),
		osg::Vec4(0.3f,0.3f,0.3f,1.0f)));

	particleTempalte.setPosition(osg::Vec3(0.0f,0.0f,0.0f));
	particleTempalte.setVelocity(osg::Vec3(0.0f,0.0f,0.0f));
	particleTempalte.setMass(0.1f);                               //单位：千克
	particleTempalte.setRadius(0.2f);

	particleTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
	particleTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
	particleTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);

	// 创建并初始化粒子系统。
	osg::ref_ptr<osgParticle::ParticleSystem> particleSystem = new osgParticle::ParticleSystem;
	particleSystem->setDataVariance(osg::Node::STATIC);

	// 设置材质，是否放射粒子，以及是否使用光照。
	particleSystem->setDefaultAttributes ("Texture/smoke.rgb",false,false);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(particleSystem);
	smokeNode->addChild(geode);

	//设置为粒子系统的缺省粒子对象。
	particleSystem ->setDefaultParticleTemplate (particleTempalte);

	//获取放射极中缺省计数器的句柄，调整每帧增加的新粒子数目
	osg::ref_ptr<osgParticle::RandomRateCounter> particleGenerateRate = new osgParticle::RandomRateCounter();
	particleGenerateRate->setRateRange(80,100);

	// 每秒新生成的粒子范围
	particleGenerateRate ->setDataVariance (osg::Node::DYNAMIC);

	// 自定义一个放置器，这里创建并初始化一个点放置器
	osg::ref_ptr<osgParticle::PointPlacer> particlePlacer = new osgParticle::PointPlacer ;
	particlePlacer->setCenter(osg::Vec3(0.0f,0.0f,10.0f));
	particlePlacer->setDataVariance(osg::Node::DYNAMIC);

	// 自定义一个弧度发射器
	osg::ref_ptr<osgParticle::RadialShooter> particleShooter = new osgParticle::RadialShooter;

	// 设置发射器的属性
	particleShooter->setDataVariance (osg::Node::DYNAMIC);
	particleShooter->setThetaRange(0.0f, 0.5f);

	// 弧度值，与Z 轴夹角
	//particleShooter->setPhiRange(0.0f,osg::PI_2);
	particleShooter->setInitialSpeedRange(10,15);                          //单位：米/秒

	//创建标准放射极对象
	osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
	emitter->setDataVariance(osg::Node::DYNAMIC);
	emitter->setCullingActive(false);
	emitter->setStartTime(2.4);

	// 将放射极对象与粒子系统关联。
	emitter->setParticleSystem(particleSystem);

	// 设置计数器
	emitter->setCounter(particleGenerateRate);

	// 设置放置器
	emitter->setPlacer(particlePlacer);

	// 设置发射器
	emitter->setShooter(particleShooter);

	// 把放射极添加为变换节点
	smokeNode->addChild(emitter);

	// 添加更新器，以实现每帧的粒子管理。
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// 将更新器与粒子系统对象关联。
	particleSystemUpdater ->addParticleSystem (particleSystem);

	// 将更新器节点添加到场景中。
	smokeNode->addChild(particleSystemUpdater);

	// 创建标准编程器对象并与粒子系统相关联。
	osg::ref_ptr<osgParticle::ModularProgram> particleMoveProgram = new osgParticle::ModularProgram;
	particleMoveProgram ->setParticleSystem (particleSystem);

	// 最后，将编程器添加到场景中。
	smokeNode->addChild(particleMoveProgram);
}
