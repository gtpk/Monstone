#pragma once
#include "IEventHandler.h"
#include <vector>
#include "Penal.h"
#include <string>


using namespace std;
namespace MarxEngine
{
	class RootUI : public Penal
	{
	private:
		vector<IEventHandler<ClickEventArgs>*> TouchEvent;


	public:
		RootUI();

	public:
		void addEventHandler(IEventHandler<ClickEventArgs>* handler);

	public:
		void onTouchEvent(MotionEvent event);


	public:
		virtual void OnCreate() { }

	public:

	public:
		virtual void OnTouch(UIBase* sender, ClickEventArgs e) {	}

	public:
		virtual void OnShow() { }

	public:
		virtual void onClose() {}

	public:
		void onUpdate(long long dt) {}

	public:
		void OnDraw(bool isSelect = false)
		{
			vector<ImageControl*>::iterator iter = m_Container->m_Child.begin();

			while (iter != m_Container->m_Child.end()) {
				ImageControl* ParentControl = *iter;
				ParentControl->OnDraw();
				vector<ImageControl*> TempList = ParentControl->getAllChild();
				vector<ImageControl*>::iterator tempitor = TempList.begin();
				while (tempitor != TempList.end())
				{
					ImageControl* DrawableControl = *tempitor;
					DrawableControl->OnDraw();
					tempitor++;
				}
				iter++;
			}
		}


		void Save()
		{
			TiXmlDocument doc;
			TiXmlElement* msg;

			//문서 설정
			TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

			doc.LinkEndChild(decl);
			// Root 만들자
			TiXmlElement * root = new TiXmlElement("RootUI");
			doc.LinkEndChild(root);


			//경고 문구삽입
			//TiXmlComment * comment = new TiXmlComment();
			//comment->SetValue("자동 완성된 코드 이므로 직접 수정 하지 마시오." );  
			//root->LinkEndChild( comment );

			TiXmlElement * MapPieces = new TiXmlElement("Child");
			root->LinkEndChild(MapPieces);

			{
				std::vector<ImageControl*>::iterator md2begin = m_Container->m_Child.begin();
				std::vector<ImageControl*>::iterator md2End = m_Container->m_Child.end();
				for (; md2begin != md2End; md2begin++)
				{
					Md2Object* node = ((Md2Object*)*md2begin);
					node->Save(MapPieces);
				}
			}

			if (MarxWorld::getInstance().Volkes != NULL)
			{
				doc.SaveFile(MarxWorld::getInstance().Volkes->SaveUrl().c_str());
			}
		}



		bool Load(string str)
		{
			TiXmlDocument doc(str.c_str());
			bool loadOkay = doc.LoadFile();

			if (!loadOkay)
			{
				// 파일이 없음..!!
				printf("File Not Found %s\n", str.c_str());
				return false;
				//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
			}


			TiXmlDeclaration* declar = doc.ToDeclaration();
			if (declar != NULL)
			{
				if (declar->Version() != "1.0")
				{
					// 버전이 일치 하지 않음
					return false;
				}
			}

			TiXmlNode* MapNode;

			MapNode = doc.FirstChild("RootUI");

			TiXmlElement* MinMonstersMap = MapNode->ToElement();

			TiXmlNode * MapPieces = MapNode->FirstChild("Child");


			{
				TiXmlNode* Piece = MapPieces->FirstChild("ImageControl");

				for (; Piece != NULL; Piece = Piece->NextSibling())
				{
					TiXmlElement* pelement = Piece->ToElement();

					const char* _Name = pelement->Attribute("Name");
					const char* _TextureName = pelement->Attribute("TextureName");
					int _transparent = 255;
					pelement->Attribute("transparent", &_transparent);
					float _ScaleX;
					pelement->QueryFloatAttribute("ScaleX", &_ScaleX);
					float _ScaleY;
					pelement->QueryFloatAttribute("ScaleY", &_ScaleY);
					float _x;
					pelement->QueryFloatAttribute("x", &_x);
					float _y;
					pelement->QueryFloatAttribute("y", &_y);
					float _zindex;
					pelement->QueryFloatAttribute("zindex", &_zindex);
					float _m_rotate;
					pelement->QueryFloatAttribute("m_rotate", &_m_rotate);
					float Width;
					pelement->QueryFloatAttribute("Width", &Width);
					float Height;
					pelement->QueryFloatAttribute("Height", &Height);

					ImageControl* child = ImageControl::CreateImageControl(
						string(_TextureName), _Name, _x, _y);
					child->SetWidth(Width);
					child->SetHeight(Height);
					child->zindex = _zindex;
					child->m_rotate = _m_rotate;
					child->ScaleX = _ScaleX;
					child->ScaleY = _ScaleY;
					addChild(child);
					child->Load(child, pelement);
				}
			}

			return false;

		}

	};
}