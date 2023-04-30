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
	// �������Ӷ������������Բ���������ϵͳʹ�á�
	osgParticle::Particle explosionTempalte;

	explosionTempalte.setShape(osgParticle::Particle::QUAD);
	explosionTempalte.setLifeTime(1.25);                                    // ��λ����
	explosionTempalte.setSizeRange (osgParticle::rangef(3.0f, 300.0f));   // ��λ����
	explosionTempalte.setAlphaRange(osgParticle::rangef(1,0));
	explosionTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(1.0f,0.2f,0.0f,1.0f),
		osg::Vec4(0.1f,0.1f,0.1f,0)));
 	explosionTempalte.setMass(2.0f);                                        //��λ��ǧ��
 	explosionTempalte.setRadius(0.5f);

 	explosionTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
    explosionTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
 	explosionTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);


	// ��������ʼ������ϵͳ��
	osg::ref_ptr<osgParticle::ParticleSystem> explosionParticleSystem = new osgParticle::ParticleSystem;
	explosionParticleSystem->setDataVariance(osg::Node::DYNAMIC);

	// ����Ϊ����ϵͳ��ȱʡ���Ӷ���
 	explosionParticleSystem ->setDefaultParticleTemplate (explosionTempalte);

	// ���ò��ʣ��Ƿ�������ӣ��Լ��Ƿ�ʹ�ù��ա�
	explosionParticleSystem->setDefaultAttributes ("Texture/fireball.sgi",true,false);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(explosionParticleSystem);
	explosion->addChild(geode);
 
 	// ��ȡ���伫��ȱʡ�������ľ��������ÿ֡���ӵ���������Ŀ
   	osg::ref_ptr<osgParticle::RandomRateCounter> particleGenerateRate = new osgParticle::RandomRateCounter();

    // ÿ�������ɵ����ӷ�Χ
    particleGenerateRate ->setDataVariance (osg::Node::DYNAMIC);
  	particleGenerateRate->setRateRange(500,600);

 
 	// �Զ���һ�������������ﴴ������ʼ��һ���������
	osg::ref_ptr<osgParticle::BoxPlacer> particlePlacer = new osgParticle::BoxPlacer ;
 	particlePlacer->setCenter(osg::Vec3(0.0f,0.0f,10.0f));
 	particlePlacer->setXRange(-1,1);
 	particlePlacer->setYRange(-1,1);
 	particlePlacer->setZRange( 0,1);
 	particlePlacer->setDataVariance(osg::Node::DYNAMIC);

	// �Զ���һ�����ȷ�����
 	osg::ref_ptr<osgParticle::RadialShooter> particleShooter = new osgParticle::RadialShooter; 
	
	// ���÷�����������
 	particleShooter->setDataVariance (osg::Node::DYNAMIC);
 
 	// xyƽ��н�
 	particleShooter->setThetaRange(0.0f, osg::PI_2);
 
 	// ����ֵ����Z ��н�
 	//particleShooter->setPhiRange(osg::PI,-osg::PI);
	particleShooter->setInitialSpeedRange(10.0,20.0f);                          //��λ����/��

	//������׼���伫��
 	osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
 	emitter->setDataVariance(osg::Node::DYNAMIC);
 	emitter->setCullingActive(false);
	emitter->setStartTime(2);
	emitter->setLifeTime(0.3);
	emitter->setEndless(false);
 
 	// �����伫����������ϵͳ������
 	emitter->setParticleSystem(explosionParticleSystem);

	// ���ü�����
    emitter->setCounter(particleGenerateRate);

	// ���÷�����
	emitter->setPlacer(particlePlacer);

	// ���÷�����
	emitter->setShooter(particleShooter);

	// �ѷ��伫���Ϊ�任�ڵ�
 	explosion->addChild(emitter);
 
	// ��Ӹ���������ʵ��ÿ֡�����ӹ���
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// ��������������ϵͳ���������
	particleSystemUpdater ->addParticleSystem (explosionParticleSystem);

	// ���������ڵ���ӵ������С�
	explosion->addChild(particleSystemUpdater);

	// ������׼���������������ϵͳ�������
	osg::ref_ptr<osgParticle::ModularProgram> particleMoveProgram = new osgParticle::ModularProgram;
	particleMoveProgram ->setParticleSystem (explosionParticleSystem);

	osg::ref_ptr<osgParticle::ExplosionOperator> operatorExplosion = new osgParticle::ExplosionOperator ;
	operatorExplosion ->setRadius(100.0f);
	operatorExplosion ->setMagnitude(500.0f);
	operatorExplosion ->setEpsilon(20.0f);
	operatorExplosion ->setSigma(30.0);

	particleMoveProgram->addOperator(operatorExplosion);

	// ��󣬽��������ӵ������С�
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
	// �������Ӷ������������Բ���������ϵͳʹ�á�
	osgParticle::Particle explosionDebrisTempalte;

	explosionDebrisTempalte.setShape(osgParticle::Particle::QUAD);
	explosionDebrisTempalte.setLifeTime(life);                                           // ��λ����
	explosionDebrisTempalte.setSizeRange (osgParticle::rangef(minSize, maxSize));        // ��λ����
	explosionDebrisTempalte.setAlphaRange(osgParticle::rangef(1.0f,1.0f));
//  	explosionDebrisTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(0.5f, 0.5f, 0.0f, 1.0f),
//  		osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f)));
	explosionDebrisTempalte.setMass(12.5f);                                               //��λ��ǧ��
	explosionDebrisTempalte.setRadius(0.33f);

	explosionDebrisTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
	explosionDebrisTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
	explosionDebrisTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);

	// ��������ʼ������ϵͳ��
	osg::ref_ptr<osgParticle::ParticleSystem> explosionDebrisParticleSystem = new osgParticle::ParticleSystem;

	explosionDebrisParticleSystem->setDataVariance(osg::Node::DYNAMIC);


	// ����Ϊ����ϵͳ��ȱʡ���Ӷ���
	explosionDebrisParticleSystem->setDefaultParticleTemplate(explosionDebrisTempalte);


	// ���ò��ʣ��Ƿ�������ӣ��Լ��Ƿ�ʹ�ù��ա�
	explosionDebrisParticleSystem->setDefaultAttributes (texture,false,false);

	osg::ref_ptr<osg::Geode> geode= new osg::Geode;
	geode->addDrawable(explosionDebrisParticleSystem);
	explosionDebris->addChild(geode);

	// ��ȡ���伫��ȱʡ�������ľ��������ÿ֡���ӵ���������Ŀ
	osg::ref_ptr<osgParticle::RandomRateCounter> particleDebrisGenerateRate = new osgParticle::RandomRateCounter();

	// ÿ�������ɵ����ӷ�Χ
	particleDebrisGenerateRate ->setDataVariance (osg::Node::DYNAMIC);
	particleDebrisGenerateRate ->setRateRange(minNum,maxNum);

	// �Զ���һ�������������ﴴ������ʼ��һ���������
	osg::ref_ptr<osgParticle::BoxPlacer> particleDebrisPlacer = new osgParticle::BoxPlacer ;
	particleDebrisPlacer->setCenter(osg::Vec3(0.0f,0.0f,10.0f));
	particleDebrisPlacer->setXRange(-1,1);
	particleDebrisPlacer->setYRange(-1,1);
	particleDebrisPlacer->setZRange( 0,1);
	particleDebrisPlacer->setDataVariance(osg::Node::DYNAMIC);

	// �Զ���һ�����ȷ�����
	osg::ref_ptr<osgParticle::RadialShooter> particleDebrisShooter = new osgParticle::RadialShooter; 

	// ���÷�����������
	particleDebrisShooter->setDataVariance (osg::Node::DYNAMIC);

	// xyƽ��н�
	particleDebrisShooter->setThetaRange(0.0f, osg::PI_2);

	// ����ֵ����Z ��н�
	//particleShooter->setPhiRange(osg::PI,-osg::PI);
	particleDebrisShooter->setInitialSpeedRange(minSpeed,maxSpeed);                          //��λ����/��

	//������׼���伫��
	osg::ref_ptr<osgParticle::ModularEmitter> emitterDebris = new osgParticle::ModularEmitter;

	emitterDebris->setDataVariance(osg::Node::DYNAMIC);
	emitterDebris->setCullingActive(false);
	emitterDebris->setStartTime(2.3);
	emitterDebris->setLifeTime(0.3);
	emitterDebris->setEndless(false);

	// �����伫����������ϵͳ������
	emitterDebris->setParticleSystem(explosionDebrisParticleSystem);

    // ���ü�����
	emitterDebris->setCounter(particleDebrisGenerateRate);

	// ���÷�����
	emitterDebris->setPlacer(particleDebrisPlacer);

	// ���÷�����
	emitterDebris->setShooter(particleDebrisShooter);

    // �ѷ��伫���Ϊ�任�ڵ�
	explosionDebris->addChild(emitterDebris);

	// ��Ӹ���������ʵ��ÿ֡�����ӹ���
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleDebrisSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// ���������ڵ���ӵ������С�
	explosionDebris->addChild(particleDebrisSystemUpdater);

    // ��������������ϵͳ���������
    particleDebrisSystemUpdater ->addParticleSystem (explosionDebrisParticleSystem);

	// ������׼���������������ϵͳ�������
    osg::ref_ptr<osgParticle::ModularProgram> particleDebrisMoveProgram = new osgParticle::ModularProgram;

    // ������׼���������������ϵͳ�������
    particleDebrisMoveProgram ->setParticleSystem (explosionDebrisParticleSystem);

	// ������Ƭ����
	osg::ref_ptr<osgParticle::AccelOperator> op_gravity = new osgParticle::AccelOperator;
	op_gravity->setToGravity();
	particleDebrisMoveProgram->addOperator(op_gravity);

	// ���ÿ�������
	osg::ref_ptr<osgParticle::FluidFrictionOperator> op_fluid_air = new osgParticle::FluidFrictionOperator;
	op_fluid_air->setFluidToAir();
	particleDebrisMoveProgram->addOperator(op_fluid_air);

    // ��󣬽��������ӵ������С�
	explosionDebris->addChild(particleDebrisMoveProgram);
}
