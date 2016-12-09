
#include <cinder/app/AppNative.h>
#include <cinder/gl/gl.h>
#include <cinder/Camera.h>
#include <cinder/Font.h>
#include <cinder/Quaternion.h>


using namespace ci;
using namespace ci::app;

class CinderProjectApp : public AppNative {
	CameraPersp camera;

	float rx, ry, rz;
	Quatf rotate;


	Font font;


public:
	void setup();

	void mouseDown(MouseEvent event);

	void update();
	void draw();
};

void CinderProjectApp::setup()
{
	// カメラを生成
	camera = CameraPersp(getWindowWidth(), getWindowHeight(),
		30.0f,
		0.1f, 100.0f);

	camera.setEyePoint(Vec3f(0, 1, -4));
	// FIXME: setEyePointの後でsetCenterOfInterestPointを呼び出す事
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 0));

	rx = ry = rz = 0;

	// フォント生成
	font = Font("Consolas", 25);

	// OpenGL設定
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	gl::enableAlphaBlending();

}

void CinderProjectApp::mouseDown(MouseEvent event)
{
	ry += 90.0f;
}



void CinderProjectApp::update()
{
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

	gl::pushMatrices();

	gl::setMatrices(camera);

	rotate = Quatf(rx, toRadians(ry), rz);
	gl::multModelView(rotate.toMatrix44());
	//gl::rotate(rotate);

	gl::drawColorCube(Vec3f(0, 0, 0), Vec3f(1, 1.5, 1));

	gl::popMatrices();

	{
		std::string text("ry:" + std::to_string(ry));
		gl::drawString(text, Vec2f(0, 0), Color(1, 1, 1), font);
	}
	{
		std::string text("rx:" + std::to_string(toDegrees(rotate.getPitch())) 
			             + " ry:" + std::to_string(toDegrees(rotate.getYaw()))
			             + " rz:" + std::to_string(toDegrees(rotate.getRoll())));

		gl::drawString(text, Vec2f(0, 30), Color(1, 1, 1), font);
	}
}


CINDER_APP_NATIVE(CinderProjectApp, RendererGl)
