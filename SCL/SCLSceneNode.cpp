#include "SCLPrerequisites.h"
#include "SCLSceneNode.h"

namespace SCL
{
	SceneNode::SceneNode(Scene* scene)
		: mScene(scene),
		  mPosition(0, 0, 0),
		  mScale(1, 1, 1),
		  mOrientation(Quaternion::IDENTITY),
		  mDerivedOrientation(Quaternion::IDENTITY),
		  mDerivedPosition(Vector3f::ZERO),
		  mDerivedScale(1, 1, 1),
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
			if (mParent)
			{
				//父节点需要更新
				const Quaternion& parentDO = mParent->getDerivedOrientation(); //获取父节点的推导方向
				mDerivedOrientation = parentDO * mOrientation;

				const Vector3f& parentDS = mParent->getDerivedScale();
				mDerivedScale = parentDS * mScale;

				mDerivedPosition = parentDO * (parentDS * mPosition);
				mDerivedPosition += mParent->getDerivedPosition();
			}
			else
			{
				//当根节点处理
				mDerivedPosition = mPosition;
				mDerivedOrientation = mOrientation;
				mDerivedScale = mScale;
			}
			mNeedParentUpdate = false;
		}

		//更新子节点
		if (mNeedChildUpdate)
		{
			for (auto child : mChilds)
			{
				child->_update();
			}

			mNeedChildUpdate = false;
		}
	}
}
