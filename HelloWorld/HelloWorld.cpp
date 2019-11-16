#include "HelloWorld.h"
//#include "Game.cpp"

HelloWorld::HelloWorld(std::string name)
 :Scene(name)
{

}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	ECS::AttachRegister(m_sceneReg);
	float aspectRatio = windowWidth / windowHeight;
	{
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}


	//Setup new Entity Health Bar
	/*
	{
		//Creates entity
		auto entity = ECS::CreateEntity();


		//Creates new orthographic camera
		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	}

*/


	{
		//Creates entity Map
		auto entityBack = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entityBack);
		ECS::AttachComponent<Transform>(entityBack);

		//Sets up components"LeagueBack.png"
		std::string LeagueBack = "Map.png"; //400, 200
		ECS::GetComponent<Sprite>(entityBack).LoadSprite(LeagueBack, 380, 200);

		ECS::GetComponent<Transform>(entityBack).SetPosition(vec3(0.f, 0.f, 13.f));
		//Setup up the Identifier
		unsigned int bitHolder = 0x0;
		ECS::SetUpIdentifier(entityBack, bitHolder, "Temp Entity");
	}



	//Setup new Entity, SpaceRanger
	{
		//Our attack animation file
		auto Moving = File::LoadJSON("SpaceRanger.json");

		//Creates entity
		auto entitySpaceRanger = ECS::CreateEntity();

		//
		EntityIdentifier::MainPlayer(entitySpaceRanger);
		//Add components
		ECS::AttachComponent<Sprite>(entitySpaceRanger);
		ECS::AttachComponent<Transform>(entitySpaceRanger);
		ECS::AttachComponent<AnimationController>(entitySpaceRanger);

		//Sets up components
		std::string SpaceRanger = "Space Rager 2.png";
		auto& animControllerr = ECS::GetComponent<AnimationController>(entitySpaceRanger);
		animControllerr.InitUVs(SpaceRanger);

		//Adds first Animation
		//animControllerr.AddAnimation(Animation());
										//Calling the name of the animation

		animControllerr.AddAnimation(Moving["MovingDown"]);
		animControllerr.AddAnimation(Moving["MovingUp"]);
		animControllerr.AddAnimation(Moving["MovingLeft"]);
		animControllerr.AddAnimation(Moving["MovingRight"]);


		//Set first anitmation
		animControllerr.SetActiveAnim(0);

		//gets first animation
		auto& anim = animControllerr.GetAnimation(0);

		//Makes it repeat
		anim.SetRepeating(true);

		//Sets the time between frames
		anim.SetSecPerFrame(0.1667f);

		ECS::GetComponent<Sprite>(entitySpaceRanger).LoadSprite(SpaceRanger, 485 / 4, 547 / 4, true, &animControllerr);
		ECS::GetComponent<Sprite>(entitySpaceRanger).SetUVs(vec2(14.f, 34.f), vec2(30.f, 11.f));
		//30, -25, 20
		ECS::GetComponent<Transform>(entitySpaceRanger).SetPosition(vec3(-85.f, -25.f, 20.f));






		//Setup up the Identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entitySpaceRanger, bitHolder, "SpaceRanger Entity");

	}

}

int HelloWorld::SpaceRanger()
{
	return m_entitySpaceRanger;
}
