#include "StdAfx.h"
#include "Fire.h"

CFire::CFire(void)
{
}

CFire::~CFire(void)
{
}

void CFire::createFireBall( osg::ref_ptr<osg::MatrixTransform> smokeNode )
{
	// �������Ӷ������������Բ���������ϵͳʹ�á�
	osgParticle::Particle particleTempalte;

	particleTempalte.setShape(osgParticle::Particle::QUAD);
	particleTempalte.setLifeTime(1.5);                             // ��λ����
	particleTempalte.setSizeRange (osgParticle::rangef(3.0f,1.0f));   // ��λ����
	particleTempalte.setAlphaRange(osgParticle::rangef(1,0));
	particleTempalte.setColorRange(osgParticle::rangev4(osg::Vec4(1.0f,0.2f,0.0f,1.0f),
		osg::Vec4(0.1f,0.1f,0.1f,0)));

	particleTempalte.setPosition(osg::Vec3(0.0f,0.0f,0.0f));
	particleTempalte.setVelocity(osg::Vec3(0.0f,0.0f,0.0f));
	particleTempalte.setMass(0.1f);                               //��λ��ǧ��
	particleTempalte.setRadius(0.2f);

	particleTempalte.setSizeInterpolator (new osgParticle::LinearInterpolator);
	particleTempalte.setAlphaInterpolator (new osgParticle::LinearInterpolator);
	particleTempalte.setColorInterpolator (new osgParticle::LinearInterpolator);

	// ��������ʼ������ϵͳ��
	osg::ref_ptr<osgParticle::ParticleSystem> particleSystem = new osgParticle::ParticleSystem;
	particleSystem->setDataVariance(osg::Node::STATIC);

	// ���ò��ʣ��Ƿ�������ӣ��Լ��Ƿ�ʹ�ù��ա�
	particleSystem->setDefaultAttributes ("Texture/smoke.rgb",true,false);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(particleSystem);
	smokeNode->addChild(geode);

	//����Ϊ����ϵͳ��ȱʡ���Ӷ���
	particleSystem ->setDefaultParticleTemplate (particleTempalte);

	//��ȡ���伫��ȱʡ�������ľ��������ÿ֡���ӵ���������Ŀ
	osg::ref_ptr<osgParticle::RandomRateCounter> particleGenerateRate = new osgParticle::RandomRateCounter();
	particleGenerateRate->setRateRange(100,500);

	// ÿ�������ɵ����ӷ�Χ
	particleGenerateRate ->setDataVariance (osg::Node::DYNAMIC);

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
	particleShooter->setThetaRange(0.0,osg::PI_4);

	// ����ֵ����Z ��н�
//	particleShooter->setPhiRange(0.0f,osg::PI_2);
	particleShooter->setInitialSpeedRange(10.0f,20.0f);                          //��λ����/��

	//������׼���伫����
	osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
	emitter->setDataVariance(osg::Node::DYNAMIC);
	emitter->setCullingActive(false);
	emitter->setStartTime(2.3);

	// �����伫����������ϵͳ������
	emitter->setParticleSystem(particleSystem);

	// ���ü�����
	emitter->setCounter(particleGenerateRate);

	// ���÷�����
	emitter->setPlacer(particlePlacer);

	// ���÷�����
	emitter->setShooter(particleShooter);

	// �ѷ��伫���Ϊ�任�ڵ�
	smokeNode->addChild(emitter);

	// ��Ӹ���������ʵ��ÿ֡�����ӹ���
	osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleSystemUpdater = new osgParticle::ParticleSystemUpdater;

	// ��������������ϵͳ���������
	particleSystemUpdater ->addParticleSystem (particleSystem);

	// ���������ڵ���ӵ������С�
	smokeNode->addChild(particleSystemUpdater);

	// ������׼���������������ϵͳ�������
	osg::ref_ptr<osgParticle::ModularProgram> particleMoveProgram = new osgParticle::ModularProgram;
	particleMoveProgram ->setParticleSystem (particleSystem);

	// ��󣬽��������ӵ������С�
	smokeNode->addChild(particleMoveProgram);
}
