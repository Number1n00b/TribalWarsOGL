
#include "Camera.h"

#include <math.h>

//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Camera::Camera(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{
	m_rotateSpeed = 0.1f;
	m_moveSpeed = 0.4f;

	ResetXYZ();

	m_deltaMoveFB = 0;
	m_deltaMoveLR = 0;
	m_deltaMoveUD = 0;

	m_rotateAngleLR = 0.0;
	m_rotateAngleUD = 0.0;
	m_deltaAngleLR = 0.0;
	m_deltaAngleUD = 0.0;

	callGLLookAt();
}

//--------------------------------------------------------------------------------------
// Reset camera values
//--------------------------------------------------------------------------------------
void Camera::ResetXYZ()
{
	
	m_lookX = 0.0f;
	m_lookY = 0.0f;
	m_lookZ = -1.0f;
	
	m_lookXX = 1.0f;
	m_lookYY = 1.0f;
	m_lookZZ = 0.0f;
}

void Camera::update(float time) {
	msgrcvr();

	pos.sy(pos.y() + 10);

	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();
	Message tmpm;

	bool in = false;

	while (tmp->hasMessage(id)) {
		in = true;
		tmpm = tmp->getMessage(id);

		if (tmpm.getInstruction() == "MVF") {
			std::cout << "MVF" << std::endl;
			DirectionFB(4);
		}
		else
		if (tmpm.getInstruction() == "MVB") {
			std::cout << "MVB" << std::endl;
			DirectionFB(-4);
		}
		else
		if (tmpm.getInstruction() == "MVR") {
			std::cout << "MVR" << std::endl;
			DirectionRotateLR(1);
		}
		else
		if (tmpm.getInstruction() == "MVL") {
			std::cout << "MVL" << std::endl;
			DirectionRotateLR(-1);
		}
		else
		if (tmpm.getInstruction() == "SFB") {
			std::cout << "SFB" << std::endl;
			DirectionFB(0);
		}
		else
		if (tmpm.getInstruction() == "SLR") {
			std::cout << "SLR" << std::endl;
			DirectionRotateLR(0);
		}
		else
		if (tmpm.getInstruction() == "LD") {
			std::cout << "LD" << std::endl;
			DirectionLookUD(-1);
		}
		else
		if (tmpm.getInstruction() == "LU") {
			std::cout << "LU" << std::endl;
			DirectionLookUD(1);
		}
		else
		if (tmpm.getInstruction() == "SUD") {
			std::cout << "SUD" << std::endl;
			DirectionLookUD(0);
		}

		std::cout << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
	}
	CheckCamera();

	callGLLookAt();
	//
}

void Camera::render() {

}

//--------------------------------------------------------------------------------------
//  Determine direction
//--------------------------------------------------------------------------------------
void Camera::DirectionFB(int const & tempMove)
{
	m_deltaMoveFB = tempMove;
}
//--------------------------------------------------------------------------------------
void Camera::DirectionLR(int const & tempMove)
{
	m_deltaMoveLR = tempMove;
}
//--------------------------------------------------------------------------------------
// Not used but allows up and don movement
void Camera::DirectionUD(int const & tempMove)
{
	m_deltaMoveUD = tempMove;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionRotateLR(GLdouble const & tempMove)
{
	m_deltaAngleLR = tempMove * m_rotateSpeed;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionLookUD(int const & tempMove)
{
	m_deltaAngleUD = tempMove * m_rotateSpeed;
}


//--------------------------------------------------------------------------------------
// Is ok to move camera backwards and forwards
//--------------------------------------------------------------------------------------
bool Camera::MoveFBOK()
{
	bool tempReturn;
	if (m_deltaMoveFB < 0 || m_deltaMoveFB > 0)
	{
		tempReturn = true;
	}
	else
	{
		tempReturn = false;
	}
	return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to move camera sideways
//--------------------------------------------------------------------------------------
bool Camera::MoveLROK()
{
	bool tempReturn;
	if (m_deltaMoveLR < 0 || m_deltaMoveLR > 0)
	{
		tempReturn = true;
	}
	else
	{
		tempReturn = false;
	}
	return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to move camera up and down (not used)
//--------------------------------------------------------------------------------------
bool Camera::MoveUDOK()
{
	bool tempReturn;
	if (m_deltaMoveUD < 0 || m_deltaMoveUD > 0)
	{
		tempReturn = true;
	}
	else
	{
		tempReturn = false;
	}
	return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to rotate sideways
//--------------------------------------------------------------------------------------
bool Camera::RotateLROK()
{
	bool tempReturn;
	if ((m_deltaAngleLR/m_rotateSpeed) < 0 || (m_deltaAngleLR/m_rotateSpeed) > 0)
	{
		tempReturn = true;
	}
	else
	{
		tempReturn = false;
	}
	return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to rotate up and down
//--------------------------------------------------------------------------------------
bool Camera::LookUDOK()
{
	bool tempReturn;
	if ((m_deltaAngleUD/m_rotateSpeed) < 0 || (m_deltaAngleUD/m_rotateSpeed) > 0)
	{
		tempReturn = true;
	}
	else
	{
		tempReturn = false;
	}
	return tempReturn;
}

//--------------------------------------------------------------------------------------
// Move camera backwards and forwards
//--------------------------------------------------------------------------------------
void Camera::MoveFB()
{
	// set movement step
	GLdouble moveZ = (m_deltaMoveFB * (m_lookZ) * m_moveSpeed);
	GLdouble moveX = (m_deltaMoveFB * (m_lookX) * m_moveSpeed);

	// increment position
	pos.sx(pos.x() + moveX);
	pos.sz(pos.z() + moveZ);

	// redisplay
	callGLLookAt();
}

//--------------------------------------------------------------------------------------
// Move camera left and right (sideways)
//--------------------------------------------------------------------------------------
void Camera::MoveLR()
{

	// set movement step
	GLdouble moveZ = (m_deltaMoveLR * (m_lookZZ) * m_moveSpeed);
	GLdouble moveX = (m_deltaMoveLR * (m_lookXX) * m_moveSpeed);
	
	pos.sx(pos.x() + moveX);
	pos.sz(pos.z() + moveZ);

	callGLLookAt();

}

//----------------------------------------------------------------------------------------
// Moves camera up and down (NOT USED)
//----------------------------------------------------------------------------------------
void Camera::MoveUD()
{
	pos.sy(m_deltaMoveUD * (m_lookYY)* m_moveSpeed);
	callGLLookAt();

}

//----------------------------------------------------------------------------------------
// Rotates camera left and right
//----------------------------------------------------------------------------------------
void Camera::RotateLR()
{
	m_rotateAngleLR += m_deltaAngleLR;
	m_lookX = sin(m_rotateAngleLR);
	m_lookZ = -cos(m_rotateAngleLR);
	m_lookXX = sin(m_rotateAngleLR + (float) PI/2.0);
	m_lookZZ = -cos(m_rotateAngleLR + (float) PI/2.0);
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
//  Rotates camera up and down
//----------------------------------------------------------------------------------------
void Camera::LookUD()
{
	m_rotateAngleUD += m_deltaAngleUD;
	m_lookY = sin(m_rotateAngleUD);
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Positions camera at co-ordinates of parameters
//----------------------------------------------------------------------------------------
void Camera::Position (GLdouble const & tempX, GLdouble const & tempY,
	GLdouble const & tempZ, GLdouble const & tempAngle, GLdouble const & tempAnglUD)
{
	ResetXYZ();
	
	pos.sx(tempX);
	pos.sy(tempY);
	pos.sy(tempZ);

	// rotate to correct angle
	m_rotateAngleLR = tempAngle * (PI / 180);
	if (tempAnglUD != 0){
		m_rotateAngleUD = tempAngle * (PI / 180);
	}
	m_lookX = sin(m_rotateAngleLR);
	m_lookZ = -cos(m_rotateAngleLR);
	//m_lookY = sin(m_rotateAngleUD);
	m_lookXX = sin(m_rotateAngleLR + (float) PI/2.0);
	m_lookZZ = -cos(m_rotateAngleLR + (float) PI/2.0);
	m_rotateAngleUD = 0.0;
	m_deltaAngleUD = 0.0;

	// redislay
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Check ok to move
//----------------------------------------------------------------------------------------
void Camera::CheckCamera()
{
	if (MoveFBOK()) MoveFB();
	if (MoveLROK()) MoveLR();
	if (MoveUDOK()) MoveUD();
	if (RotateLROK()) RotateLR();
	if (LookUDOK()) LookUD();
}


//----------------------------------------------------------------------------------------
//  Redisplay new camera view
//----------------------------------------------------------------------------------------
void Camera::callGLLookAt()
{
	Singleton<RenderModuleStubb>::getInstance()->callLookAt(vec3(pos.x(), pos.y(), pos.z()), vec3(pos.x() + m_lookX, pos.y() + m_lookY, pos.z() + m_lookZ), vec3(0,1,0));
	//glLoadIdentity();
	//gluLookAt(pos.x(), pos.y(), pos.z(), 
	//	pos.x() + m_lookX, pos.y() + m_lookY, pos.z() + m_lookZ,
	//		  0.0f, 1.0f, 0.0f);

}



