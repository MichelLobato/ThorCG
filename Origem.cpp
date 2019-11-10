#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <GLU.H>
#include <GL.H>
#include <math.h>
//#include "textura.h"
// Usei como base para criação desse codigo o projeto do avião, para o sietema de cordenadas, o sistema de saturno foi todo feito do 0.

//#pragma warning(disable : 4996); 
//#define pi 4*atan(1)

GLfloat Rotatex;

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotZ, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;


// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao(void)
{
	GLfloat luzAmbiente[4] = { 0.5,0.5,0.5,1.0 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor" 
	GLfloat luzEspecular[4] = { 2.0, 2.0, 2.0, 1.0 };// "brilho" 
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 60;

	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

/*
int LoadBitmapTexture(const char* filename, int glId)
{
	FILE* file; // Ponteiro da struct FILE
	char temp;
	long i;

	//BITMAPINFOHEADER infoheader; // Struct do cabeçalho que tem as informações do arquivo Bitmap


	if ((file = fopen(filename, "rb")) == NULL) { // Abre o arquivo para leitura - rb ( read binary )
		return (-1);
	}
	fseek(file, 18, SEEK_CUR);
	fread(&infoheader.biWidth, sizeof(int), 1, file); // Armazena em biWidth o tamanho da largura da imagem

	fread(&infoheader.biHeight, sizeof(int), 1, file); // Armazena em biHeight o tamanho da altura da imagem

	fread(&infoheader.biPlanes, sizeof(short int), 1, file); // Armazena as coordenadas das cores da imagem
	if (infoheader.biPlanes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
		return -1;
	}

	// read the bpp
	fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file); // Le o numero de bits por pixel
	if (infoheader.biBitCount != 24) {
		printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
		return -1;
	}

	fseek(file, 24, SEEK_CUR);

	// read the data.
	char* data = (char*)malloc(infoheader.biWidth * infoheader.biHeight * 3);// Armazena os dados
	if (data == NULL) {
		printf("Error allocating memory for color-corrected image data\n");
		return -1;
	}

	if ((i = fread(data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {// Le os dados armazenados
		printf("Error reading image data from %s.\n", filename);
		return -1;
	}

	fclose(file); // Fecha o arquivo

	for (i = 0; i < (infoheader.biWidth * infoheader.biHeight * 3); i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}

	glBindTexture(GL_TEXTURE_2D, glId); // Bind the ID texture specified by the 2nd parameter

										// The next commands sets the texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

																					 //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // We don't combine the color with the original surface color, use only the texture map.

																					 // Finally we define the 2d texture
																					 //glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

																					 // And create 2d mipmaps for the minifying function
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

	free(data); // Free the memory we used to load the texture

	return (glId); // Returns the current texture OpenGL ID
}*/


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	//----------------------------------------------------------
	glColor3f(1.0f, 1.0f, 1.0f);
	// frente
	glVertex3f(2.5, 3.5, 9);
	glVertex3f(2.5, 5.5, 9);
	glVertex3f(3, 6, 9);
	glVertex3f(5, 6, 9);
	glVertex3f(5.5, 5.5, 9);
	glVertex3f(5.5, 3.5, 9);
	glVertex3f(5, 3, 9);
	glVertex3f(3, 3, 9);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	//Face frente inclinada superior direita
	glVertex3f(5, 6, 9);
	glVertex3f(5.25, 6.5, 8);
	glVertex3f(6, 5.75, 8);
	glVertex3f(5.5, 5.5, 9);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	//Face frente lateral inclinada direita 
	glVertex3f(6, 5.75, 8);
	glVertex3f(5.5, 5.5, 9);
	glVertex3f(5.5, 3.5, 9);
	glVertex3f(6, 3.25, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	//Face frente inclinada inferior direita
	glVertex3f(5.5, 3.5, 9);
	glVertex3f(6, 3.25, 8);
	glVertex3f(5.25, 2.5, 8);
	glVertex3f(5, 3, 9);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face frente inclinada inferior central
	glVertex3f(5, 3, 9);
	glVertex3f(5.25, 2.5, 8);
	glVertex3f(2.75, 2.5, 8);
	glVertex3f(3, 3, 9);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face frente inclinda inferior esquerda
	glVertex3f(3, 3, 9);
	glVertex3f(2.5, 3.5, 9);
	glVertex3f(2, 3.25, 8);
	glVertex3f(2.75, 2.5, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face frente laterial inclinada esquerda
	glVertex3f(2, 3.25, 8);
	glVertex3f(2, 5.75, 8);
	glVertex3f(2.5, 5.5, 9);
	glVertex3f(2.5, 3.5, 9);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face frente inclinada superior esquerda
	glVertex3f(3, 6, 9);
	glVertex3f(2.5, 5.5, 9);
	glVertex3f(2, 5.75, 8);
	glVertex3f(2.75, 6.5, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face frente central superior
	glVertex3f(3, 6, 9);
	glVertex3f(5, 6, 9);
	glVertex3f(5.25, 6.5, 8);
	glVertex3f(2.75, 6.5, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face lateral direita
	glVertex3f(6, 5.75, 8);
	glVertex3f(6, 3.25, 8);
	glVertex3f(6, 3.25, 1);
	glVertex3f(6, 5.75, 1);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face lateral inclinada superior
	glVertex3f(6, 5.75, 8);
	glVertex3f(5.25, 6.5, 8);
	glVertex3f(5.25, 6.5, 1);
	glVertex3f(6, 5.75, 1);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face lateral inferior direita 
	glVertex3f(5.25, 2.5, 8);
	glVertex3f(5.25, 2.5, 6.6);
	glVertex3f(5.6, 2.85, 6.6);
	glVertex3f(5.6, 2.85, 6.5);
	glVertex3f(5.25, 2.5, 6.5);
	glVertex3f(5.25, 2.5, 2.6);
	glVertex3f(5.6, 2.85, 2.6);
	glVertex3f(5.6, 2.85, 2.5);
	glVertex3f(5.25, 2.5, 2.5);
	glVertex3f(5.25, 2.5, 1);
	glVertex3f(6, 3.25, 1);
	glVertex3f(6, 3.25, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face inferio partes 3
	glVertex3f(5.25, 2.5, 1);
	glVertex3f(2.75, 2.5, 1);
	glVertex3f(2.75, 2.5, 2.5);
	glVertex3f(5.25, 2.5, 2.5);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face inferior parte 2
	glVertex3f(2.75, 2.5, 6.5);
	glVertex3f(5.25, 2.5, 6.5);
	glVertex3f(5.25, 2.5, 2.6);
	glVertex3f(2.75, 2.5, 2.6);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face inferior parte 1
	glVertex3f(2.75, 2.5, 6.6);
	glVertex3f(5.25, 2.5, 6.6);
	glVertex3f(5.25, 2.5, 8);
	glVertex3f(2.75, 2.5, 8);
	glEnd();
	//----------------------------------------------------------
	glBegin(GL_LINE_LOOP);
	// Face trasiera
	glVertex3f(2.5, 3.5, 0);
	glVertex3f(2.5, 5.5, 0);
	glVertex3f(3, 6, 0);
	glVertex3f(5, 6, 0);
	glVertex3f(5.5, 5.5, 0);
	glVertex3f(5.5, 3.5, 0);
	glVertex3f(5, 3, 0);
	glVertex3f(3, 3, 0);
	glEnd();



	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Posiciona e orienta o observador
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle, fAspect, 0.5, 500);

	PosicionaObservador();
}

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	8.0
#define SENS_OBS	10.0
#define SENS_TRANSL	5.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo 
	if (bot == GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}
	// Botão direito 
	else if (bot == GLUT_RIGHT_BUTTON)
	{
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// Calcula diferença
		int deltaz = deltax - deltay;

		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}
	// Botão do meio 
	else if (bot == GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle = 10;

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	obsX = obsY = 0;
	obsZ = 150;
}

void Idle(void) {
	Rotatex += 0.01;
	Desenha();
}

// Função Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Martelo do funking Thorr");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	glutIdleFunc(Idle);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}