#include "HudWindow.h"
#include "MessengerEvents/Common.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "UI/UIWindow.h"
#include <Serialization/Types/SerializationFieldRef.h>

namespace asteroids
{
    REGISTER_CLASS_LOADER_TEST(HudWindow);

    void HudWindow::Init()
    {
        InitSubscriptions();
    }

    void HudWindow::OnWindowOpen()
    {
        UpdateValues();
    }

    void HudWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UITextComponent>>>(_lives, "lives", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UITextComponent>>>(_score, "score", weak_from_this());
    }

    void HudWindow::InitSubscriptions()
    {
        _subscriptions.Reset();
        _subscriptions.Subscribe<UpdateHud>([&](const auto&)
        {
            UpdateValues();
        });
    }

    void HudWindow::UpdateValues()
    {
        auto window = GetWindow();
        auto systems = window->GetSystemsManager();
        if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
        {
            if (auto lives = _lives.Get())
            {
                const int livesValue = playerInfo->GetResource(ResourceType::Lives);
                lives->SetText(std::to_string(livesValue));
            }

            if (auto score = _score.Get())
            {
                const int scoreValue = playerInfo->GetResource(ResourceType::Score);
                score->SetText(std::to_string(scoreValue));
            }
        }
    }
}
