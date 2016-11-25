#include"../uTinyEngine/include/Game.h"
#include<iostream>
#include<vector>
#include"../uTinyEngine/include/Renderer.h"
#include"../uTinyEngine/include/Time.h"
#include"../uTinyEngine/include/Console.h"
#pragma comment(lib, "../Debug/uTinyEngine.lib")

class Controller : public Script {

	float speed = 0;
	float rotationSpeed = 0;

	static void Increase(float* value, float delta, float max) {
		*value += delta;
		if (*value > max)
			*value = max;
	}
	static void Decrease(float* value, float delta, float min) {
		*value -= delta;
		if (*value < min)
			*value = min;
	}
	static void Balance(float* value, float delta, float balance) {
		if (*value > balance)
			Decrease(value, delta, balance);
		if (*value < balance)
			Increase(value, delta, balance);
	}
	Material* leftTrack = nullptr;
	Material* rightTrack = nullptr;

	std::vector<Transform*> bigWheelRight;
	std::vector<Transform*> bigWheelLeft;
	std::vector<Transform*> smallWheelRight;
	std::vector<Transform*> smallWheelLeft;

	Transform* turret;
	Transform* cannon;

	void Start() override {
		leftTrack = gameObject()->FindChildRecursively("track_left")->GetComponent<Material>();
		rightTrack = gameObject()->FindChildRecursively("track_right")->GetComponent<Material>();

		bigWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_2")->GetComponent<Transform>());
		bigWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_3")->GetComponent<Transform>());
		bigWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_4")->GetComponent<Transform>());
		bigWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_5")->GetComponent<Transform>());
		bigWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_6")->GetComponent<Transform>());

		bigWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_2")->GetComponent<Transform>());
		bigWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_3")->GetComponent<Transform>());
		bigWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_4")->GetComponent<Transform>());
		bigWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_5")->GetComponent<Transform>());
		bigWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_6")->GetComponent<Transform>());

		smallWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_1")->GetComponent<Transform>());
		smallWheelRight.push_back(gameObject()->FindChildRecursively("wheel_r_7")->GetComponent<Transform>());

		smallWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_1")->GetComponent<Transform>());
		smallWheelLeft.push_back(gameObject()->FindChildRecursively("wheel_l_7")->GetComponent<Transform>());

		turret = gameObject()->FindChildRecursively("turret")->GetComponent<Transform>();
		cannon = gameObject()->FindChildRecursively("cannon")->GetComponent<Transform>();
	}

	void Update() override {

		float dt = Time::DeltaTime();		

		static int sumCount = 0;
		static float sum = 0;

		sumCount++;
		sum += dt;

		if (sumCount > 5 || sumCount < 0) {

			char buffer[16];
			sprintf(buffer, "%.3f FPS", sumCount/sum );
			Console::Current()->Clear();
			Console::Current()->WriteLine(buffer, strlen(buffer));
			sumCount = 0;
			sum = 0;
		}

		if (Input::GetKeyDown(Key::W))
			Increase(&speed, 2 * dt, 10);
		else if (Input::GetKeyDown(Key::S))
			Decrease(&speed, 2 * dt, -10);
		else
			Balance(&speed, 3 * dt, 0);

		if (Input::GetKeyDown(Key::A))
			Increase(&rotationSpeed, 50 * dt, 60);
		else if (Input::GetKeyDown(Key::D))
			Decrease(&rotationSpeed, 50 * dt, -60);
		else
			Balance(&rotationSpeed, 50 * dt, 0);

		transform()->Translate(transform()->Forward()*speed*dt);
		transform()->Rotate(Vector3::Up(), rotationSpeed*dt);

		float dl = (speed * 5 - rotationSpeed*0.23f)*dt;
		float dr = (speed * 5 + rotationSpeed*0.23f)*dt;
		leftTrack->uvTransform->uvOffset[1] += dl;
		rightTrack->uvTransform->uvOffset[1] += dr;

		for (int i = 0;i < 5;i++) {
			bigWheelLeft[i]->Rotate(Vector3::Right(), -dl * 153 / 5);
			bigWheelRight[i]->Rotate(Vector3::Right(), -dr * 153 / 5);
		}
		for (int i = 0;i < 2;i++) {
			smallWheelLeft[i]->Rotate(Vector3::Right(), -dl * 230 / 5);
			smallWheelRight[i]->Rotate(Vector3::Right(), -dr * 230 / 5);
		}

		if (Input::GetKeyDown(Key::J))
			turret->rotation.y += 30 * dt;
		if (Input::GetKeyDown(Key::L))
			turret->rotation.y -= 30 * dt;

		if (Input::GetKeyDown(Key::I))
			cannon->rotation.x -= 30 * dt;
		if (Input::GetKeyDown(Key::K))
			cannon->rotation.x += 30 * dt;
	}
};

class CameraController :public Script {
	GameObject* child = nullptr;
public:
	Transform* following = nullptr;
	void Start() override {
		child = gameObject()->GetChild()[0].get();
	}
	void Update() override {
		if (Input::GetKeyDown(Key::Mouse_Left)) {
			auto d = Input::GetMousePositionChange();
			gameObject()->GetComponent<Transform>()->rotation.y -= d.x;
			gameObject()->GetComponent<Transform>()->rotation.x += d.y;
		}

		if (following)
			gameObject()->GetComponent<Transform>()->translation = following->translation + Vector3::Up() * 3;

	}
};

class MyGame : public Game {
public:
	MyGame() {
		this->scene = std::unique_ptr<Scene>(new Scene());
		this->scene->LoadModel("../resource/t34_76.fbx");
		this->scene->LoadModel("../resource/xidian.fbx", scene.get());
		this->scene->LoadModel("../resource/sky.fbx", scene.get());
		this->scene->AddComponent(new GridRenderer);

		Camera* cam = new Camera();
		cam->SetAsMainCamera();

		auto r = scene->FindChildRecursively("Model");
		if (r != nullptr)
			r->SetScript<Controller>();

		auto textureBody = Texture::CreateFromFile("../resource/body.tex");
		Material* materialBody = new Material();
		materialBody->texture.push_back(std::shared_ptr<Texture>(textureBody));

		Material* materialTrackRight = new Material();
		Material* materialTrackLeft = new Material();
		
		Texture* texTrack = Texture::CreateFromFile("../resource/track.tex");
		materialTrackRight->texture.push_back(std::shared_ptr<Texture>(texTrack));
		materialTrackLeft->texture.push_back(std::shared_ptr<Texture>(texTrack));

		Material* materialWheel = new Material();
		Texture* texWheel = Texture::CreateFromFile("../resource/wheel.tex");
		materialWheel->texture.push_back(std::shared_ptr<Texture>(texWheel));

		GameObject::Dump(scene.get());

		Material::AssignMaterial(scene->FindChildRecursively("track_left"), materialTrackLeft);
		Material::AssignMaterial(scene->FindChildRecursively("track_right"), materialTrackRight);
		Material::AssignMaterial(scene->FindChildRecursively("wheels"), materialWheel);
		Material::AssignMaterial(scene->FindChildRecursively("Model"), materialBody);

		Material* materialSky = new Material();
		materialSky->lighting = false;
		Texture* texSky = Texture::CreateFromFile("../resource/sky.tex");
		materialSky->texture.push_back(std::shared_ptr<Texture>(texSky));

		Material::AssignMaterial(scene->FindChildRecursively("sky"), materialSky);

		Material* materialGround = new Material();
		Texture* texGround = Texture::CreateFromFile("../resource/ground.tex");
		materialGround->texture.push_back(std::shared_ptr<Texture>(texGround));
		Material::AssignMaterial(scene->FindChildRecursively("Ground"), materialGround, true);

		GameObject* CamCenter = new GameObject();
		CamCenter->SetScript<CameraController>();
		GameObject* CamObj = new GameObject();
		CamObj->AddComponent(cam);
		CamObj->GetComponent<Transform>()->translation.z = -7;

		scene->AddChild(CamCenter);
		CamCenter->AddChild(CamObj);
		CamCenter->GetScript<CameraController>()->following = r->GetComponent<Transform>();

		cam->SetSkyObject(scene->FindChildRecursively("sky"));
	}
};


int main() {
	return Game::Run(new MyGame);
}