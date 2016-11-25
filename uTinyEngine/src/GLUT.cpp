#include<map>


#include "freeGLUT\glut.h"

#define UTINY_API __declspec(dllexport)

#include "../include/Input.h"

#include "../include/Game.h"
#include "../include/Transform.h"
#include "../include/Camera.h"
#include "../include/Renderer.h"
#include "../include/Material.h"
#include "../include/Font.h"
#include "../include/Console.h"
//#pragma comment(lib, "freeGLUT/freeglut.lib")

void display();
void reshape(int width, int height);
void setupInput();
void updateInput();
void updateTransform(GameObject* root);
static Game* pGame = NULL;

GLfloat sun_light_position[] = { 1000.0f, 1000.0f, 1000.0f, 1.0f };
GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


Texture* testTex;
Font* testFont;
Console console;
int Game::Run(Game* game) {
	//TODO: Setup and run glut
	pGame = game;


	int argc = 1;
	char* argv[]{ "OpenGL" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	setupInput();

	//������Ⱦ����

	glClearColor(0.4f, 0.4f, 0.4f, 1);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//debug
	//glEnable(GL_LIGHT0);
	testFont = Font::Create();
	testTex = testFont->RenderChar(67);
	console.Resize(40, 20);
	//console.WriteLine(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52);
	console.SetAsCurrent();
	

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //ָ����0�Ź�Դ��λ��   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ�  
														 //�����ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //�������~~  
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//���淴���~~~  

	GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };//������  
	GLfloat material_diffuse[] = { 1, 1, 1, 1.0 };//�������  
	GLfloat material_specular[] = { 0, 0, 0, 1.0 };//�����  

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);//���ʻ�����  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//�����������  
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);//���ʾ����

	glEnable(GL_LIGHT0); //ʹ�õ�0�Ź���  
	glEnable(GL_LIGHTING); //�ں������Ⱦ��ʹ�ù���  

	if (pGame->scene != nullptr)
		pGame->scene->Start();

	//glutFullScreen();
	glutMainLoop();

	return 0;
}

float viewMatrix[16];
void drawConsole(Console* con);
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//debug
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*gluLookAt(3, 2, 4, 1, 1, -1, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
	glLoadIdentity();*/
	auto cam_mat = Camera::Main()->transform()->WorldMatrix;
	gluLookAt(cam_mat[3][0], cam_mat[3][1], cam_mat[3][2],
		cam_mat[3][0] + cam_mat[2][0], cam_mat[3][1] + cam_mat[2][1], cam_mat[3][2] + cam_mat[2][2],
		cam_mat[1][0], cam_mat[1][1], cam_mat[1][2]
	);
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
	glLoadIdentity();

	updateTransform((pGame->scene).get());
	//glTranslatef(0, 1, 0);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.3333f, 1, 100);*/

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(viewMatrix);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glPopMatrix();

	if (pGame->scene != nullptr)
		pGame->scene->Update();

	drawConsole(Console::Current());

	glutSwapBuffers();
	updateInput();
}

void reshape(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluPerspective(60, (float)width / (float)height, 1, 1500);

}

extern std::map<Key, KeyState> keyStates;
extern std::map<Key, KeyEvent> keyEvents;

extern MousePosition lastMousePosition;
extern MousePosition currentMousePosition;


//���̰���
void keyboardFunc(unsigned char key, int x, int y) {
	keyStates[(Key)key] = KeyState::Down;
}
//�����ɿ�
void keyboardUpFunc(unsigned char key, int x, int y)
{
	//std::cout << "Key Up: key char = " << key << "  key ascii = " << (int)key << std::endl;
	keyStates[(Key)key] = KeyState::Up;
}



//��갴��
void mouseFunc(int button, int state, int x, int y) {
	KeyState s;
	Key k;
	if (button == GLUT_LEFT_BUTTON) k = Key::Mouse_Left;
	if (button == GLUT_RIGHT_BUTTON) k = Key::Mouse_Right;
	if (button == GLUT_MIDDLE_BUTTON) k = Key::Mouse_Middle;

	if (state == GLUT_UP) s = KeyState::Up;
	if (state == GLUT_DOWN) s = KeyState::Down;

	keyStates[k] = s;
}

//����ƶ�
void motionFunc(int x, int y) {
	//debug 
	//std::cout << "Mouse Motion: x = " << x << " y = " << y << std::endl;
	currentMousePosition.x = x;
	currentMousePosition.y = y;
}

//������ƶ�
void passiveMotionFunc(int x, int y) {
	//std::cout << "Passive Mouse Motion: x = " << x << " y = " << y << std::endl;
	motionFunc(x, y);
}

//����GLUT�ļ�������¼��ص�����
void setupInput()
{
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutPassiveMotionFunc(motionFunc);
}

//���������¼״̬��ÿ��Ⱦһ֡����һ�θ���
void updateInput()
{
	lastMousePosition = currentMousePosition;
}

void updateTransform(GameObject* root) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	Transform* t = root->GetComponent<Transform>();
	if (t != nullptr)
	{
		glPushMatrix();
		glLoadIdentity();

		glTranslatef(t->translation.x, t->translation.y, t->translation.z);
		glRotatef(t->rotation.z, 0, 0, 1);
		glRotatef(t->rotation.y, 0, 1, 0);
		glRotatef(t->rotation.x, 1, 0, 0);
		glScalef(t->scale.x, t->scale.y, t->scale.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)t->LocalMatrix);
		glPopMatrix();

		glMultMatrixf((float*)t->LocalMatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)t->WorldMatrix);
	}
	auto child = root->GetChildList();
	for (auto i = child.begin();i != child.end();i++) {
		updateTransform(i->get());
	}
	glPopMatrix();
}



void Renderer::Render() {
	glEnable(GL_LIGHTING);
	auto transform = this->gameObject->GetComponent<Transform>();
	if (transform)
	{
		glMatrixMode(GL_MODELVIEW);
		/*glLoadMatrixf((float*)transform->WorldMatrix);
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);*/
		glLoadMatrixf(viewMatrix);
		glMultMatrixf((float*)transform->WorldMatrix);
	}

	auto mat = this->gameObject->GetComponent<Material>();
	//Texture* baseTexture = nullptr;
	UVTransform* uvtransform = nullptr;
	if (mat && mat->texture.size() > 0) {
		glEnable(GL_TEXTURE_2D);
		auto tex = mat->texture[0];
		if (tex)
		{
			//baseTexture = tex.get();
			//glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixelData);
		}
		uvtransform = mat->uvTransform.get();
		if (mat->lighting) {
			glEnable(GL_LIGHTING);
		}
		else {
			glDisable(GL_LIGHTING);
		}
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}
	auto mesh = this->gameObject->GetComponent<Mesh>();
	if (!mesh)
		return;
	VertexFormat* v = (VertexFormat*)mesh->GetMeshData();

	int triangleCount = mesh->GetTriangleCount();
	glColor3f(1, 1, 1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (int i = 0;i < triangleCount * 3;i++) {
		glNormal3fv(v[i].Normal);
		//glTexCoord2fv(v[i].UV);
		if (uvtransform)
			glTexCoord2f(v[i].u + uvtransform->uvOffset[0], v[i].v + uvtransform->uvOffset[1]);
		glVertex3fv(v[i].Position);
	}
	glEnd();
}

void GridRenderer::Render() {
	auto transform = this->gameObject->GetComponent<Transform>();
	if (transform)
	{
		//glLoadMatrixf((float*)transform->WorldMatrix);
		glLoadMatrixf(viewMatrix);
		glMultMatrixf((float*)transform->WorldMatrix);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor4f(1, 1, 1, 0.8f);
	int gridSize = 10;
	int lineSpace = 1;
	for (int i = 1;i <= gridSize;i++)
	{
		glVertex3f(i*lineSpace, 0, gridSize*lineSpace);
		glVertex3f(i*lineSpace, 0, -gridSize*lineSpace);

		glVertex3f(gridSize*lineSpace, 0, i*lineSpace);
		glVertex3f(-gridSize*lineSpace, 0, i*lineSpace);

		glVertex3f(-i*lineSpace, 0, gridSize*lineSpace);
		glVertex3f(-i*lineSpace, 0, -gridSize*lineSpace);

		glVertex3f(gridSize*lineSpace, 0, -i*lineSpace);
		glVertex3f(-gridSize*lineSpace, 0, -i*lineSpace);
	}

	glVertex3f(0, 0, 0);
	glVertex3f(-gridSize*lineSpace, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, -gridSize*lineSpace, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -gridSize*lineSpace);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(gridSize*lineSpace, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, gridSize*lineSpace, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, gridSize*lineSpace);

	glEnd();
	glEnable(GL_TEXTURE_2D);
}


Vector3 Transform::Forward() {
	return Vector3(
		-LocalMatrix[2][0],
		-LocalMatrix[2][1],
		-LocalMatrix[2][2]);
}

Vector3 Transform::Right() {
	return Vector3(
		LocalMatrix[0][0],
		LocalMatrix[0][1],
		LocalMatrix[0][2]);
}

Vector3 Transform::Up() {
	return Vector3(
		LocalMatrix[1][0],
		LocalMatrix[1][1],
		LocalMatrix[1][2]);
}

void Transform::Translate(Vector3 v)
{
	/*LocalMatrix[3][0] += v.x;
	LocalMatrix[3][1] += v.y;
	LocalMatrix[3][2] += v.z;*/
	translation = translation + v;
}
#define _180_PI 57.2957795131
void Transform::Rotate(Vector3 axis, float angle)
{
	//rotation.y += angle;
	float m[4][4];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//glGetFloatv(GL_MODELVIEW_MATRIX, (float*)m);
	//glLoadIdentity();
	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);


	glRotatef(angle, axis.x, axis.y, axis.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*)m);
	glPopMatrix();
	rotation.y = -asin(m[0][2])*_180_PI;
	rotation.x = atan2(m[1][2], m[2][2])*_180_PI;
	rotation.z = atan2(m[0][1], m[0][0])*_180_PI;

}

void Transform::Scale(Vector3 s)
{
	scale.x *= s.x;
	scale.y *= s.y;
	scale.z *= s.z;
}

std::vector<size_t> Transform::RequiredComponents()
{
	return std::vector<size_t>();
}

Transform Transform::World() {
	return Transform();
}


void drawConsole(Console* con) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	Font* font = con->GetFont();
	auto content = con->GetContent();



	float boderWidth = 2.0f / con->Width();
	float boderHeight = 2.0f / con->Height();

	int lineno = 0;
	for (auto r = content->begin();r != content->end();r++) {
		int len = r->size();
		
		for (int c = 0;c < len;c++) {

			wchar_t character = (*r)[c];
			Texture* tex = font->RenderChar(character);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->Width(), tex->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->GetPixel());


			//glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);


			glTexCoord2f(0, 1);
			glVertex3f(-1 + boderWidth*c, 1 - boderHeight*(lineno+1), 0);

			glTexCoord2f(1, 1);
			glVertex3f(-1 + boderWidth*(c + 1), 1 - boderHeight*(lineno + 1), 0);

			glTexCoord2f(1, 0);
			glVertex3f(-1 + boderWidth*(c + 1), 1 - boderHeight*lineno, 0);

			glTexCoord2f(0, 0);
			glVertex3f(-1 + boderWidth*c, 1 - boderHeight*lineno, 0);
			glEnd();


		}


		lineno++;

	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();



}