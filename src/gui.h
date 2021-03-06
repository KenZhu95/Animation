#ifndef SKINNING_GUI_H
#define SKINNING_GUI_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "tictoc.h"

struct Mesh;

/*
 * Hint: call glUniformMatrix4fv on thest pointers
 */
struct MatrixPointers {
	const float *projection, *model, *view;
};

class GUI {
public:
	GUI(GLFWwindow*, int view_width = -1, int view_height = -1, int preview_height = -1);
	~GUI();
	void assignMesh(Mesh*);

	void keyCallback(int key, int scancode, int action, int mods);
	void mousePosCallback(double mouse_x, double mouse_y);
	void mouseButtonCallback(int button, int action, int mods);
	void mouseScrollCallback(double dx, double dy);
	void updateMatrices();
	MatrixPointers getMatrixPointers() const;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double dx, double dy);

	glm::vec3 getCenter() const { return center_; }
	const glm::vec3& getCamera() const { return eye_; }
	bool isPoseDirty() const { return pose_changed_; }
	void clearPose() { pose_changed_ = false; }
	const float* getLightPositionPtr() const { return &light_position_[0]; }
	
	int getCurrentBone() const { return current_bone_; }
	int getCurrentFrame() const { return current_frame_; }
	const int* getCurrentBonePointer() const { return &current_bone_; }
	bool setCurrentBone(int i);

	bool isTransparent() const { return transparent_; }
	bool isPlaying() const { return play_; }
	bool isCreatingFrame() const { return if_create_frame; }
	bool isDeletingFrame() const { return if_delete_frame; }
	bool isUpdatingFrame() const { return if_update_frame; }
	bool isInsertingFrame() const { return if_insert_frame; }
	bool isLoadingFromJson() const { return if_load_from_json; }
	bool isCursor() const { return if_cursor; }
	bool isSavingVideo() const { return if_save_video; }
	void setCreateFrame(bool is) {
		if_create_frame = is;
	}
	void setDeleteFrame(bool is) {
		if_delete_frame = is;
	}
	void setUpdateFrame(bool is) {
		if_update_frame = is;
	}
	void setInsertFrame(bool is) {
		if_insert_frame = is;
	}
	void setLoadFromJson(bool is) {
		if_load_from_json = is;
	}
	void setSaveVideo(bool is) {
		if_save_video = is;
	}
	void currentFrameUp() {
		if (current_frame_ > 0) {
			current_frame_ --;
		}
	}

	void currentFrameDown() {
		if (current_frame_ > -1) {
			current_frame_ ++;
		}
	}
	float getCurrentPlayTime();
	float getFrameShift() const { return frame_shift_; }
	// int getMaxShift() {
	// 	return preview_height_ * mesh_->key_frames.size() - window_height_ ;
	// }

private:
	GLFWwindow* window_;
	Mesh* mesh_;

	int window_width_, window_height_;
	int view_width_, view_height_;
	int preview_height_;
	int scroll_bar_width = 25;

	bool drag_state_ = false;
	bool fps_mode_ = false;
	bool pose_changed_ = true;
	bool transparent_ = false;
	bool translation_mode_ = false;
	bool if_create_frame = false;
	bool if_delete_frame = false;
	bool if_update_frame = false;
	bool if_insert_frame = false;
	bool if_load_from_json = false;
	bool if_cursor = false;
	bool if_drag_scroll = false;
	bool if_save_video = false;
	int current_bone_ = -1;
	int current_button_ = -1;
	int current_frame_ = -1;
	float roll_speed_ = M_PI / 64.0f;
	float last_x_ = 0.0f, last_y_ = 0.0f, current_x_ = 0.0f, current_y_ = 0.0f;
	float camera_distance_ = 30.0;
	float pan_speed_ = 0.1f;
	float rotation_speed_ = 0.02f;
	float zoom_speed_ = 0.1f;
	float aspect_;

	float frame_shift_ = 0.0f;

	glm::vec3 eye_ = glm::vec3(0.0f, 0.1f, camera_distance_);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 look_ = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 tangent_ = glm::cross(look_, up_);
	glm::vec3 center_ = eye_ - camera_distance_ * look_;
	glm::mat3 orientation_ = glm::mat3(tangent_, up_, look_);
	glm::vec4 light_position_;

	glm::mat4 view_matrix_ = glm::lookAt(eye_, center_, up_);
	glm::mat4 projection_matrix_;
	glm::mat4 model_matrix_ = glm::mat4(1.0f);

	bool captureWASDUPDOWN(int key, int action);

	bool play_ = false;
	float time_ = 0.0;
	TicTocTimer timer_ = tic();
};

#endif
