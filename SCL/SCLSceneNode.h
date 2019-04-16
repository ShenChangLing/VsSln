#pragma once
#include "SCLPrerequisites.h"
#include <deque>

namespace SCL
{
	// 场景中用于显示的场景节点
	class SCL_DLL SceneNode
	{
		friend class Scene;
	public:
	protected:
		SceneNode(Scene* scene);
		~SceneNode();

	public:
		Scene* getScene() { return mScene; }
		SceneNode* getParent() { return mParent; }
		void setParent(SceneNode* scene_node) { mParent = scene_node; }

		void setPosition(const Vector3f& position);
		const Vector3f& getPosition() const { return mPosition; }

		void setOrientation(const Quaternion& orientation);
		const Quaternion& getOrientation() const { return mOrientation; }

		void setScale(const Vector3f& scale);
		const Vector3f& getScale() const { return mScale; }

		const Quaternion& getDerivedOrientation() const { return mDerivedOrientation; } //获取推到的方向
		const Vector3f& getDerivedScale() const { return mDerivedScale; }
		const Vector3f& getDerivedPosition() const { return mDerivedPosition; }

		void addChild(SceneNode* scene_node);
		void removeChild(SceneNode* scene_node);
		void removeAllChild();
		uint getChildCount();

		void attachObject(MovableObject* obj);//绑定渲染对象到当前节点
		void detachObject(MovableObject* obj);//分离
		void detachAllObjects(void);//分离所有对象

	private:
		//需要更新
		void _needupdate();
		void _update();
	protected:
		SCL_AUTO_MUTEX;
		Scene* mScene;
		Vector3f mPosition; //相对父节点的位置
		Vector3f mScale; //缩放值
		Quaternion mOrientation; //方向

	protected:
		Quaternion mDerivedOrientation; //推导出来的方向
		Vector3f mDerivedPosition; //推导出来的位置
		Vector3f mDerivedScale; //推导出来的缩放值

		SceneNode* mParent; //父节点
		SceneNodeList mChilds; //子节点

	protected:
		typedef std::deque<MovableObject*> MovableObjectList;
		MovableObjectList mMovableObjects;//绑定在当前节点的可移动渲染对象

	private:
		bool mNeedParentUpdate; //需要更新父节点
		bool mNeedChildUpdate; //需要更新子节点
	};
}
