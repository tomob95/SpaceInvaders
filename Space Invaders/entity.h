#pragma once
#if !defined(__ENTITY_H__)
#define __ENTITY_H__
// Library Includes
// Local Includes
// Types
// Constants
// Prototypes
class CSprite;
class CEntity
{
// Member Functions
public:
CEntity();
virtual ~CEntity();
virtual bool Initialise(const int _kiSpriteID);
virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);
virtual void Draw();
virtual void Process(float _fDeltaTick);
void SetX(int _i);
void SetY(int _i);
int GetX() const;
int GetY() const;
int GetHeight() const;
int GetWidth() const;
protected:
private:
CEntity(const CEntity& _kr);
CEntity& operator= (const CEntity& _kr);
// Member Variables
public:
protected:
CSprite* m_pSprite;
int m_fX;
int m_fY;
private:
};
#endif // __ENTITY_H__