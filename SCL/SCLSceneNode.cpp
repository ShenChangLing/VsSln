#include "SCLPrerequisites.h"
#include "SCLSceneNode.h"

namespace SCL
{
	SceneNode::SceneNode(Scene* scene)
		: mScene(scene),
		  mPosition(0, 0, 0),
		  mOrientation(0, 0, 0, 1),
		  mDerivedOrientation(0, 0, 0, 1),
		  mParent(nullptr),
		  mNeedParentUpdate(true),
		  mNeedChildUpdate(true)
	{
		mChilds.clear();

		_needupdate();
	}


	SceneNode::~SceneNode()
	{
		removeAllChild();
	}

	void SceneNode::setPosition(const Vector3f& position)
	{
		mPosition = position;
	}

	void SceneNode::setOrientation(const Quaternion& orientation)
	{
		mOrientation = orientation;
		mOrientation.normalise();

		_needupdate();
	}

	void SceneNode::addChild(SceneNode* scene_node)
	{
		SCL_AUTO_LOCK_MUTEX;

		SceneNode* snOfParent = scene_node->getParent();

		if (snOfParent)
		{
			if (snOfParent == this)
			{
				return;
			}
			snOfParent->removeChild(scene_node);
		}

		scene_node->setParent(this);
		mChilds.push_back(scene_node);
	}

	void SceneNode::removeChild(SceneNode* scene_node)
	{
		SCL_AUTO_LOCK_MUTEX;
		scene_node->setParent(nullptr);
		mChilds.remove(scene_node);
	}

	void SceneNode::removeAllChild()
	{
		SCL_AUTO_LOCK_MUTEX;
		for (auto child : mChilds)
		{
			child->setParent(nullptr);
		}
		mChilds.clear();
	}

	uint SceneNode::getChildCount()
	{
		return mChilds.size();
	}

	void SceneNode::_needupdate()
	{
		mNeedChildUpdate = true;
		mNeedParentUpdate = true;
	}

	void SceneNode::_update()
	{
		if (mNeedParentUpdate)
		{
			//父节点需要更新
			const Quaternion& parentDO = mParent->getDerivedOrientation(); //获取父节点的推导方向
			mDerivedOrientation = parentDO * mOrientation;
		}
	}
}
