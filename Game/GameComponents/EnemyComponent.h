#pragma once
#include "Components/CharacterComponent.h"

class EnemyComponent : public phoenix::CharacterComponent
{
public:
	CLASS_DECLARATION(EnemyComponent)

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(phoenix::Actor* other) override;
	virtual void OnCollisionExit(phoenix::Actor* other) override;

	virtual void OnNotify(const phoenix::Event& event) override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

};