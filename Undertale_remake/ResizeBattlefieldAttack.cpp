#include "ResizeBattlefieldAttack.h"

ResizeBattlefieldAttack::ResizeBattlefieldAttack(uint64_t duration) :
	Attack(duration), originalSize{0, 0}, finalSize({0, 0}), startTime(0)
{
}

void ResizeBattlefieldAttack::SetFinalSize(Vector2 finalSize)
{
	this->finalSize = finalSize;
}

void ResizeBattlefieldAttack::Setup()
{
	Rectangle originalBoundary = battlefield->GetBoundary();
	originalSize = { originalBoundary.width, originalBoundary.height };
	finalSize = {originalSize.x + 100, originalSize.y + 50};
	startTime = timeSinceEpochMillisec();
}

void ResizeBattlefieldAttack::Update()
{
	float t = map(
		timeSinceEpochMillisec() - startTime,
		0, duration, 0, 1
	);
	if (t > 1)
		t = 1;
	float newWidth = lerp(originalSize.x, finalSize.x, t);
	float newHeight = lerp(originalSize.y, finalSize.y, t);
	//std::cout << newWidth << ' ' << newHeight << std::endl;
	battlefield->Resize(newWidth, newHeight);
}
