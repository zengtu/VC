#include "StdAfx.h"
#include "Explosion.h"

CExplosion::CExplosion(void)
{
	
}

CExplosion::~CExplosion(void)
{
}

void CExplosion::createExplosion( osg::ref_ptr<osg::MatrixTransform> explosion )
{
	// 创建粒子对象，设置其属性并交由粒子系统使用。
	osgParticle::Particle explosionTempalte;

	explosionTempalte.setShape(osgParticle::Particle::QUAD);
	explosionTempalte.setLifeTime(1.25);                                    // 单位：秒
	explosionTempalte.setSizeRange (osgParticle::rangef(3.0f, 300.0f));   // 单位：米
	explosionTempalte.setAlphaRange(osgParticle::rangef(1,0));
	explosionTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(1.0f,0.2f,0.0f,1.0f),
		osg::Vec4(0.1f,0.1f,0.1f,0)));
 	explosionTempalte.setMass(2.0f);                                        //单位：千克
 	explosionTempalte.setRadius(0.5f);

 	explosionTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
    explosionTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
 	explosionTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);


	// 创建并初始化粒子系统。
	osg::ref_ptr<osgParticle::ParticleSystem> explosionParticleSystem = new osgParticle::ParticleSystem;
	explosionParticleSystem->setDataVariance(osg::Node::DYNAMIC);

	// 设置为粒子系统的缺省粒子对象。
 	explosionParticleSystem ->setDefaultParticleTemplate (explosionTempalte);

	// 设置材质，是否放射粒子，以及是否使用光照。
	explosionParticleSystem->setDefaultAttributes ("Texture/fireball.sgi",true,false);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(explosionParticleSystem);
	explosion->addChild(geode);
 
 	// 获取放射极中缺省计数器的句柄，调整每帧增加的新粒子数目
   	osg::ref_ptr<osgParticle::RandomRateCounter> particleGenerateRate = new osgParticle::RandomRateCounter();

    // 每秒新生成的粒子范围
    particleGenerateRate ->setDataVariance (osg::Node::DYNAMIC);
  	particleGenerateRate->setRateRange(500,600);

 
 	// 自定义一个放置器，这里创建并初始化一个点放置器
	osg::ref_ptr<osgParticle::BoxPlacer> particlePlacer = new osgParticle::BoxPlacer ;
 	particlePlacer->setCenter(osg::Vec3(0.0f,0.0f,10.0f));
 	particlePlacer->setXRange(-1,1);
 	particlePlacer->setYRange(-1,1);
 	particlePlacer->setZRange( 0,1);
 	particlePlacer->setDataVariance(osg::Node::DYNAMIC);

	// 自定义一个弧度发射器
 	osg::ref_ptr<osgParticle::RadialShooter> particleShooter = new osgParticle::RadialShooter; 
	
	// 设置发射器的属性
 	particleShooter->setDataVariance (osg::Node::DYNAMIC);
 
 	// xy平面夹角
 	particleShooter->setThetaRange(0.0f, osg::PI_2);
 
 	// 弧度值，与Z 轴夹角
 	//particleShooter->setPhiRange(osg::PI,-osg::PI);
	particleShooter->setInitialSpeedRange(10.0,20.0f);                          //单位：米/秒

	//创建标准放射极对
 	osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
 	emitter->setDataVariance(osg::Node::DYNAMIC);
 	emitter->setCullingActive(false);
	emitter->setStartTime(2);
	emitter->setLifeTime(0.3);
	emitter->setEndless(false);
 
 	// 将放射极对象与粒子系统关联。
 	emitter->setParticleSystem(explosionParticleSystem);

	// 设置计数器
    emitter->setCounter(particleGenerateRate);

	// 设置放置器
	emitter->setPlacer(particlePlacer);

	// 设置发射器
	emitter->setShooter(particleShooter);

	// 把放射极添加为变换节点
 	explosion->addChild(emitter);
 
	// 添加更新器，以实现每帧的粒子管理。
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// 将更新器与粒子系统对象关联。
	particleSystemUpdater ->addParticleSystem (explosionParticleSystem);

	// 将更新器节点添加到场景中。
	explosion->addChild(particleSystemUpdater);

	// 创建标准编程器对象并与粒子系统相关联。
	osg::ref_ptr<osgParticle::ModularProgram> particleMoveProgram = new osgParticle::ModularProgram;
	particleMoveProgram ->setParticleSystem (explosionParticleSystem);

	osg::ref_ptr<osgParticle::ExplosionOperator> operatorExplosion = new osgParticle::ExplosionOperator ;
	operatorExplosion ->setRadius(100.0f);
	operatorExplosion ->setMagnitude(500.0f);
	operatorExplosion ->setEpsilon(20.0f);
	operatorExplosion ->setSigma(30.0);

	particleMoveProgram->addOperator(operatorExplosion);

	// 最后，将编程器添加到场景中。
	explosion->addChild(particleMoveProgram);
}

void CExplosion::createExplosionDebris( osg::ref_ptr<osg::MatrixTransform> explosionDebris, 
									   char* texture,
									   float life,
									   float minSize, 
									   float maxSize, 
									   float minNum,
									   float maxNum,
									   float minSpeed,
									   float maxSpeed )
{
	// 创建粒子对象，设置其属性并交由粒子系统使用。
	osgParticle::Particle explosionDebrisTempalte;

	explosionDebrisTempalte.setShape(osgParticle::Particle::QUAD);
	explosionDebrisTempalte.setLifeTime(life);                                           // 单位：秒
	explosionDebrisTempalte.setSizeRange (osgParticle::rangef(minSize, maxSize));        // 单位：米
	explosionDebrisTempalte.setAlphaRange(osgParticle::rangef(1.0f,1.0f));
//  	explosionDebrisTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(0.5f, 0.5f, 0.0f, 1.0f),
//  		osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)));
	explosionDebrisTempalte.setMass(12.5f);                                               //单位：千克
	explosionDebrisTempalte.setRadius(0.33f);

	explosionDebrisTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
	explosionDebrisTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
	explosionDebrisTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);

	// 创建并初始化粒子系统。
	osg::ref_ptr<osgParticle::ParticleSystem> explosionDebrisParticleSystem = new osgParticle::ParticleSystem;

	explosionDebrisParticleSystem->setDataVariance(osg::Node::DYNAMIC);


	// 设置为粒子系统的缺省粒子对象。
	explosionDebrisParticleSystem->setDefaultParticleTemplate(explosionDebrisTempalte);


	// 设置材质，是否放射粒子，以及是否使用光照。
	explosionDebrisParticleSystem->setDefaultAttributes (texture,false,false);

	osg::ref_ptr<osg::Geode> geode= new osg::Geode;
	geode->addDrawable(explosionDebrisParticleSystem);
	explosionDebris->addChild(geode);

	// 获取放射极中缺省计数器的句柄，调整每帧增加的新粒子数目
	osg::ref_ptr<osgParticle::RandomRateCounter> particleDebrisGenerateRate = new osgParticle::RandomRateCounter();

	// 每秒新生成的粒子范围
	particleDebrisGenerateRate ->setDataVariance (osg::Node::DYNAMIC);
	particleDebrisGenerateRate ->setRateRange(minNum,maxNum);

	// 自定义一个放置器，这里创建并初始化一个点放置器
	osg::ref_ptr<osgParticle::BoxPlacer> particleDebrisPlacer = new osgParticle::BoxPlacer ;
	particleDebrisPlacer->setCenter(osg::Vec3(0.0f,0.0f,10.0f));
	particleDebrisPlacer->setXRange(-1,1);
	particleDebrisPlacer->setYRange(-1,1);
	particleDebrisPlacer->setZRange( 0,1);
	particleDebrisPlacer->setDataVariance(osg::Node::DYNAMIC);

	// 自定义一个弧度发射器
	osg::ref_ptr<osgParticle::RadialShooter> particleDebrisShooter = new osgParticle::RadialShooter; 

	// 设置发射器的属性
	particleDebrisShooter->setDataVariance (osg::Node::DYNAMIC);

	// xy平面夹角
	particleDebrisShooter->setThetaRange(0.0f, osg::PI_2);

	// 弧度值，与Z 轴夹角
	//particleShooter->setPhiRange(osg::PI,-osg::PI);
	particleDebrisShooter->setInitialSpeedRange(minSpeed,maxSpeed);                          //单位：米/秒

	//创建标准放射极对
	osg::ref_ptr<osgParticle::ModularEmitter> emitterDebris = new osgParticle::ModularEmitter;

	emitterDebris->setDataVariance(osg::Node::DYNAMIC);
	emitterDebris->setCullingActive(false);
	emitterDebris->setStartTime(2.3);
	emitterDebris->setLifeTime(0.3);
	emitterDebris->setEndless(false);

	// 将放射极对象与粒子系统关联。
	emitterDebris->setParticleSystem(explosionDebrisParticleSystem);

    // 设置计数器
	emitterDebris->setCounter(particleDebrisGenerateRate);

	// 设置放置器
	emitterDebris->setPlacer(particleDebrisPlacer);

	// 设置发射器
	emitterDebris->setShooter(particleDebrisShooter);

    // 把放射极添加为变换节点
	explosionDebris->addChild(emitterDebris);

	// 添加更新器，以实现每帧的粒子管理。
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleDebrisSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// 将更新器节点添加到场景中。
	explosionDebris->addChild(particleDebrisSystemUpdater);

    // 将更新器与粒子系统对象关联。
    particleDebrisSystemUpdater ->addParticleSystem (explosionDebrisParticleSystem);

	// 创建标准编程器对象并与粒子系统相关联。
    osg::ref_ptr<osgParticle::ModularProgram> particleDebrisMoveProgram = new osgParticle::ModularProgram;

    // 创建标准编程器对象并与粒子系统相关联。
    particleDebrisMoveProgram ->setParticleSystem (explosionDebrisParticleSystem);

	// 设置碎片重力
	osg::ref_ptr<osgParticle::AccelOperator> op_gravity = new osgParticle::AccelOperator;
	op_gravity->setToGravity();
	particleDebrisMoveProgram->addOperator(op_gravity);

	// 设置空气阻力
	osg::ref_ptr<osgParticle::FluidFrictionOperator> op_fluid_air = new osgParticle::FluidFrictionOperator;
	op_fluid_air->setFluidToAir();
	particleDebrisMoveProgram->addOperator(op_fluid_air);

    // 最后，将编程器添加到场景中。
	explosionDebris->addChild(particleDebrisMoveProgram);
}
