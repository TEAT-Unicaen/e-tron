#include "color.h"

dx::XMFLOAT4 Color::toFloat4() const noexcept {
	return dx::XMFLOAT4{this->r, this->g, this->b, this->a};
}

dx::XMFLOAT3 Color::toFloat3() const noexcept {
	return dx::XMFLOAT3{ this->r, this->g, this->b };
}

D2D1::ColorF Color::toD2D1ColorF() const noexcept {
	return D2D1::ColorF(this->r, this->g, this->b, this->a);
}

std::string Color::toString() const {
	return '(' + std::to_string(this->r) + ", " + std::to_string(this->g) + ", " + std::to_string(this->b) + ", " + std::to_string(this->a) + ')';
}

Color Color::getRandomColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    Color color(0, 0, 0, 1.0f);

    do {
        float r = dis(gen);
        float g = dis(gen);
        float b = dis(gen);

        // Calcul de la luminance relative (approximation simple)
        float luminance = 0.2126f * r + 0.7152f * g + 0.0722f * b;

        // Vérifier que la couleur n'est ni trop sombre ni trop claire
        if (luminance > 0.2f && luminance < 0.8f) {
            color = Color(r, g, b, 1.0f);
            break;
        }
    } while (true);

    return color;
}

const Color Color::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color Color::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };

const Color Color::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const Color Color::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const Color Color::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };

const Color Color::YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
const Color Color::CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
const Color Color::MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };

const Color Color::SILVER = { 0.75f, 0.75f, 0.75f, 1.0f };
const Color Color::GRAY = { 0.5f, 0.5f, 0.5f, 1.0f };