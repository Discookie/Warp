//
// Created by Boldizsár Poór (boldar99@gmail.com) on 2020. 03. 22..
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "scene/scene_messenger.h"

class SceneMessengerFixture : public ::testing::Test {
protected:
    SceneMessenger scene_messenger;
    SceneMessengerFixture() : scene_messenger() {}
};

TEST_F(SceneMessengerFixture, InitTest) { EXPECT_FALSE(scene_messenger.get_scene()); }

TEST_F(SceneMessengerFixture, GetSwichTest) {
    scene_messenger.switch_scene("test_scene1");
    EXPECT_EQ(scene_messenger.get_scene(), "test_scene1");
    scene_messenger.switch_scene("test_scene2");
    EXPECT_EQ(scene_messenger.get_scene(), "test_scene2");
    scene_messenger.switch_scene("test_scene3");
    EXPECT_EQ(scene_messenger.get_scene(), "test_scene3");
}

class TestScene : public Scene {
protected:
    const unsigned int id;
    void render_scene(SceneMessenger &messenger, const ALLEGRO_EVENT &event) override {}

public:
    explicit TestScene(unsigned int id) : id(id) {}
    [[nodiscard]] unsigned int get_id() const { return id; }
};

class SceneManagerFixture : public ::testing::Test {
protected:
    SceneManager scene_manager;
    std::vector<std::unique_ptr<TestScene>> test_scenes;
    SceneManagerFixture() : scene_manager(), test_scenes() {}

    void require_test_scenes(unsigned int n) {
        test_scenes.resize(n);
        for (unsigned int i = 0; i < n; ++i) {
            test_scenes[i] = std::make_unique<TestScene>(i);
        }
    }

    [[nodiscard]] TestScene *extract_from_scene_manager(const std::string &scene_to_remove) {
        return dynamic_cast<TestScene *>(scene_manager.remove_scene(scene_to_remove).value().get());
    }

    void add_n_set(const std::string &scene, int id) {
        scene_manager.add_scene(scene, std::move(test_scenes[id]));
        scene_manager.set_scene(scene);
    }
};

TEST_F(SceneManagerFixture, InitTest) {
    require_test_scenes(4);
    ASSERT_EQ(test_scenes[0]->get_id(), 0);
    ASSERT_EQ(test_scenes[1]->get_id(), 1);
    ASSERT_EQ(test_scenes[2]->get_id(), 2);
    ASSERT_EQ(test_scenes[3]->get_id(), 3);

    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, AddSceneTest) {
    require_test_scenes(1);

    scene_manager.add_scene("0", std::move(test_scenes[0]));
    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, AddExistingSceneTest) {
    TestScene *return_scene;
    require_test_scenes(4);

    scene_manager.add_scene("scene", std::move(test_scenes[0]));
    scene_manager.add_scene("scene", std::move(test_scenes[1]), false);
    return_scene = extract_from_scene_manager("scene");
    EXPECT_EQ(return_scene->get_id(), 0);

    scene_manager.add_scene("scene", std::move(test_scenes[2]));
    scene_manager.add_scene("scene", std::move(test_scenes[3]), true);
    return_scene = extract_from_scene_manager("scene");
    EXPECT_EQ(return_scene->get_id(), 3);
}

TEST_F(SceneManagerFixture, AddExitTest) {
    require_test_scenes(2);

    add_n_set("scene", 0);
    scene_manager.add_scene("exit", std::move(test_scenes[1]));
    EXPECT_FALSE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, AddSceneWothoutReplaceTest) {
    require_test_scenes(1);

    scene_manager.add_scene("scene", std::move(test_scenes[0]));
    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, SetSceneTest) {
    require_test_scenes(1);
    add_n_set("scene", 0);
    EXPECT_FALSE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, SetMoreScenesTest) {
    require_test_scenes(2);

    scene_manager.add_scene("0", std::move(test_scenes[0]));
    add_n_set("1", 1);
    EXPECT_FALSE(scene_manager.is_exited());
    scene_manager.set_scene("0");
    EXPECT_FALSE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, SetInvalidSceneTest) {
    require_test_scenes(1);

    scene_manager.add_scene("scene", std::move(test_scenes[0]));
    scene_manager.set_scene("invalid");
    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, SetExitSceneTest) {
    require_test_scenes(1);

    add_n_set("scene", 0);
    EXPECT_FALSE(scene_manager.is_exited());

    scene_manager.set_scene("exit");
    EXPECT_TRUE(scene_manager.is_exited());
}
TEST_F(SceneManagerFixture, SetEmptySceneTest) {
    require_test_scenes(1);

    add_n_set("scene", 0);
    EXPECT_FALSE(scene_manager.is_exited());

    scene_manager.set_scene("");
    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, RemoveSceneTest) {
    TestScene *scene;
    require_test_scenes(2);

    add_n_set("active", 0);
    scene_manager.add_scene("inactive", std::move(test_scenes[1]));
    scene = extract_from_scene_manager("inactive");
    EXPECT_EQ(scene->get_id(), 1);
    EXPECT_FALSE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, RemoveActiveSceneTest) {
    require_test_scenes(1);

    add_n_set("scene", 0);
    TestScene *scene = extract_from_scene_manager("scene");
    EXPECT_EQ(scene->get_id(), 0);
    EXPECT_TRUE(scene_manager.is_exited());
}

TEST_F(SceneManagerFixture, RemoveInvalidSceneTest) {
    EXPECT_FALSE(scene_manager.remove_scene("invalid"));
}

TEST_F(SceneManagerFixture, RemoveExitSceneTest) {
    EXPECT_FALSE(*scene_manager.remove_scene("exit"));
}

TEST_F(SceneManagerFixture, RemoveEmptySceneTest) { EXPECT_FALSE(scene_manager.remove_scene("")); }

#pragma clang diagnostic pop
