#pragma once
#include <vector>
#include "uielement.h"
#include "uibackground.h"

class UIScreen {
protected:
    std::vector<UIElement*> elements;

public:
    void setBackground(const sf::Texture& texture) {
        UIBackground* background = new UIBackground(texture);
        elements.insert(elements.begin(), background); // Фон рисуется первым
    }

    virtual void handleEvent(const sf::Event& event) {
        for (unsigned int i = 0; i < elements.size(); ++i) {
            elements[i]->handleEvent(event);
        }
    }

    virtual void update() {
        for (unsigned int i = 0; i < elements.size(); ++i) {
            elements[i]->update();
        }
    }

    virtual void draw(sf::RenderWindow& window) {
        for (unsigned int i = 0; i < elements.size(); ++i) {
            elements[i]->draw(window);
        }
    }

    void addElement(UIElement* element) {
        elements.push_back(element);
    }

    virtual ~UIScreen() {
        for (unsigned int i = 0; i < elements.size(); ++i) {
            delete elements[i];
        }
        elements.clear();
    }
};

