








//
//


//
//	MeshInstance* arrowO = new MeshInstance();
//	arrowO->mesh = arrow;
//
//	actors.push_back(arrowO);
//
//
//	std::map<uint32_t, Ship*> ids;
//
//
//	Ship* player_ship = new Ship();
//	player_ship->meshInstance = new MeshInstance();
//	player_ship->meshInstance->mesh = ship01_mesh;
//	actors.push_back(player_ship);
//	player_ship->name = "babooshka";
//	ids[1] = player_ship;
//	player_ship->id = 1;
//
//
//	for (int i = 2; i < 15; i++) {
//		Ship* _ship = new Ship();
//		_ship->meshInstance = new MeshInstance();
//		_ship->meshInstance->mesh = ship01_mesh;
//		actors.push_back(_ship);
//		_ship->name = random.generate_random_name();
//		_ship->id = i;
//		_ship->is_enemy = true;
//		_ship->transform.position.x = i * 100 * (random.randfloat());
//		_ship->transform.position.z = 100 * (random.randfloat());
//		ids[i] = _ship;
//	}
//	
//	
//
//


//
//		glm::mat4 projection(1.0f);
//		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 5500.0f);
//
//		double xpos, ypos;
//		glfwGetCursorPos(window, &xpos, &ypos);
//	
//		float x = (2.0f * xpos) / window_width - 1.0f;
//		float y = 1.0f - (2.0f * ypos) / window_height;
//
//
//		glm::vec4 screenPos = glm::vec4(x,y , -1.0f, 1.0f);
//		glm::vec4 rayEye = glm::inverse(projection) * screenPos;
//		rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
//
//		glm::vec4 rayWorld4 = glm::inverse(camera->view) * rayEye;
//		glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld4));
//
//		glm::vec3 mouseWorldPos  = camera->position + rayDir * 150.0f;
//		
//
//		if (selected == nullptr) {
//			arrowO->visible = false;
//		}
//		else {
//			arrowO->visible = true;
//			arrowO->transform.position = selected->end_pos;
//			arrowO->transform.position.y += 2;
//		}
//		
//		
//		arrowO->transform.scale = glm::vec3(0.3, 0.3, 0.3);
//		arrowO->transform.position.y += sin(glfwGetTime()*2.0) / 3.0;
//		arrowO->transform.rotation.y += 0.01;
//		
//
//		shader.Use();
//		shader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
//		shader.setVec3("viewPos", camera->position);
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", camera->view);
//
//
//
//		int n = 0;
//		for (PointLight* light : lights) {
//			shader.setVec3("pointLights[" + std::to_string(n) + "].position", light->transform.position);
//			shader.setVec3("pointLights[" + std::to_string(n) + "].color", light->color);
//			shader.setFloat("pointLights[" + std::to_string(n) + "].strength", light->strength);
//			shader.setFloat("pointLights[" + std::to_string(n) + "].radius", light->radius);
//			n += 1;
//		}
//		shader.setInt("light_number", n);
//		
//
//		//pick
//		glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);
//		glClearColor(0, 0, 0, 1);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glViewport(0, 0, window_width, window_height);
//		shader.setBool("color_mode", true);
//
//		for (auto const& [id, ship] : ids)
//		{
//			shader.setVec3("color_color", glm::vec3(id / 255.0f, 0.0, 0.0));
//			ship->draw();
//		}
//
//		unsigned char pixel[3];
//		glReadPixels(xpos, window_height - ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//		uint32_t selectedID = pixel[0];
//
//		if (lclick == true) {
//
//			if (selected == nullptr) {
//				if (ids.count(selectedID)) {
//					selected = ids[selectedID];
//				}
//			}
//
//			else {
//				if (selectedID == 0) {
//					if (selected->can_control == true) {
//						selected->navigate(mouseWorldPos);
//					}
//					else {
//						selected = nullptr;
//					}
//				}
//
//				else {
//					if (selected->can_control == true) {
//						if (selected != ids[selectedID]) {
//							if (ids[selectedID]->is_enemy) {
//								selected->attack(ids[selectedID]);
//							}
//						}
//					}
//				}
//
//			}
//			lclick = false;
//		}
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		shader.setBool("color_mode", false);
//
//
//
//
//		for (GameActor* actor : actors) {
//			actor->update();
//			actor->draw();
//
//
//
//		}
//
//		shader.Use();
//		shader.setBool("color_mode", true);
//		for (auto const& [id, ship] : ids)
//		{
//			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//			ship->transform.scale += glm::vec3(0.1f, 0.1f, 0.1f);
//
//			if (ship->is_enemy) {
//				shader.setVec3("color_color", glm::vec3(1.0f, 0.0f, 0.0f));
//			}
//			else {
//				shader.setVec3("color_color", glm::vec3(0.0f, 0.2f, 1.0f));
//			}
//
//			if (ship->is_enemy) {
//					ship->next_move += 1;
//
//					if (ship->next_move == 100) {
//						ship->next_move = 0;
//						ship->attack(player_ship);
//				}
//			}
//
//			
//
//
//
//			ship->draw();
//			ship->transform.scale -= glm::vec3(0.1f, 0.1f, 0.1f);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//
//
//			
//
//
//
//
//		}
//		shader.setBool("color_mode", false);
//
//		float logicalWidth = 100.0f; //????
//		float logicalHeight = logicalWidth / aspectRatio;
//
//		glm::mat4 proj = glm::ortho(
//			0.0f, logicalWidth,
//			0.0f, logicalHeight,
//			-1.0f, 1.0f
//		);
//
//
//		glDisable(GL_CULL_FACE);
//
//
//		glClear(GL_DEPTH_BUFFER_BIT);
//		
//		if (selected != nullptr) {
//			font.draw("name > " + selected->name, glm::vec2(1.0, logicalHeight - 1.0f), &proj);
//			font.draw("speed > " + std::to_string(selected->speed * selected->acc), glm::vec2(1.0, logicalHeight - 4.0f), &proj);
//		}
//
//		
//
//		for (auto const& [id, ship] : ids)
//		{
//			fontShader.Use();
//
//			glDisable(GL_CULL_FACE);
//
//			glm::mat4 model = glm::mat4(1.0);
//
//			Transform _temp = ship->transform;
//			_temp.position.y += 1;
//
//
//			float distance = glm::length(camera->position - _temp.position);
//			float scale = distance * 0.004f;
//
//			model = glm::translate(model, _temp.position);
//			model = glm::scale(model, glm::vec3(scale));
//
//			glm::vec3 directionToCamera = glm::normalize(camera->position - glm::vec3(model[3][0], model[3][1], model[3][1]));
//			float angle = atan2(directionToCamera.x, directionToCamera.z);
//			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
//
//			model = model * rotationMatrix;
//
//			fontShader.setBool("in_world", true);
//			fontShader.setMat4("model", model);
//			fontShader.setMat4("view", camera->view);
//			font.draw(ship->name +"\n"+std::to_string(ship->health) , glm::vec2(0.0, 0.0), &projection);
//			fontShader.setBool("in_world", false);
//
//
//			glEnable(GL_CULL_FACE);
//		}
//
//
//		font.color = glm::vec3(1.0, 0.0, 0.0);
//		font.draw(std::to_string(glfwGetTime()), glm::vec2(glfwGetTime(), glfwGetTime()), &proj);
//		font.color = glm::vec3(1.0, 1.0, 1.0);
//
//		
//
//		glEnable(GL_CULL_FACE);
//
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//
//
//
//	glfwTerminate();
//
//
//	return 0;
//}
//

