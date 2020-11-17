#pragma once
class GamePlayStatic
{
public:
	static void SetMainGame(class MainGame* mainGameObject) { mainGame = mainGameObject; }
	static class MainGame* GetMainGame() { return mainGame; }

	static void SetPlayerCharacter(class Character* character) { playerCharacter = character; }
	static class Character* GetPlayerCharacter() { return playerCharacter; }

	static void SetScene(class Scene* sceneObject) {scene = sceneObject;}
	static class Scene* GetScene() { return scene; }
private:
	static class MainGame* mainGame;
	static class Character* playerCharacter;
	static class Scene* scene;
};

