#pragma once

#include "TestRegistry.hpp"
#include "TestRunner.hpp"
#include "TestResult.hpp"

#include "PrimitiveArrayRawPointerMap.hpp"
#include "PrimitiveMapPolicy.hpp"

namespace pankey{

	namespace Type{

		namespace Map{

			namespace Test{

				using PrimitiveIntegerMap = pankey::DataStructure::Map::PrimitiveArrayRawPointerMap<
					pankey::DataStructure::Map::PrimitiveMapPolicy<int, int>
				>;

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_1(pankey::Utility::Test::TestResult& a_result){
					PrimitiveIntegerMap i_map;
					int* i_key = new int(1);
					int* i_value = new int(10);

					a_result.assertTrue(0, "Map should start empty", i_map.isEmpty());
					a_result.assertEqual(0, "Initial length should be zero", i_map.length(), 0);
					a_result.assertEqual(0, "Initial capacity should be zero", i_map.getSize(), 0);
					a_result.assertTrue(0, "Insertion without capacity should fail", !i_map.addPointers(i_key, i_value));
					a_result.assertNull(0, "Invalid key lookup should return null", i_map.getKeyPointerByIndex(0));
					a_result.assertNull(0, "Invalid value lookup should return null", i_map.getValuePointerByIndex(0));

					delete i_key;
					delete i_value;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_2(pankey::Utility::Test::TestResult& a_result){
					int* i_key_1 = new int(1);
					int* i_key_2 = new int(2);
					int* i_key_3 = new int(3);
					int* i_value_1 = new int(10);
					int* i_value_2 = new int(20);
					int* i_value_3 = new int(30);

					{
						PrimitiveIntegerMap i_map;
						a_result.assertTrue(0, "Capacity allocation should succeed", i_map.expandLocalSize(2));
						a_result.assertEqual(0, "Capacity should be two", i_map.getSize(), 2);
						a_result.assertTrue(0, "First insertion should succeed", i_map.addPointers(i_key_1, i_value_1));
						a_result.assertTrue(0, "Second insertion should succeed", i_map.addPointers(i_key_2, i_value_2));
						a_result.assertTrue(0, "Insertion past capacity should fail", !i_map.addPointers(i_key_3, i_value_3));
						a_result.assertEqual(0, "Length should remain two", i_map.length(), 2);
						a_result.assertTrue(0, "First key pointer should be preserved", i_map.getKeyPointerByIndex(0) == i_key_1);
						a_result.assertTrue(0, "Second value pointer should be preserved", i_map.getValuePointerByIndex(1) == i_value_2);
						a_result.assertTrue(0, "Pair lookup should find the inserted pair", i_map.containPairPointers(i_key_1, i_value_1));
						a_result.assertTrue(0, "Key lookup should find the inserted key", i_map.getKeyIndexByPointer(i_key_2) == 1);
						a_result.assertTrue(0, "Value lookup should find the inserted value", i_map.getValueIndexByPointer(i_value_1) == 0);
					}

					delete i_key_1;
					delete i_key_2;
					delete i_key_3;
					delete i_value_1;
					delete i_value_2;
					delete i_value_3;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_3(pankey::Utility::Test::TestResult& a_result){
					int* i_key_1 = new int(1);
					int* i_key_2 = new int(2);
					int* i_key_replacement = new int(3);
					int* i_value_1 = new int(10);
					int* i_value_2 = new int(20);
					int* i_value_replacement = new int(30);

					{
						PrimitiveIntegerMap i_map;
						i_map.expandLocalSize(3);
						i_map.addPointers(i_key_1, i_value_1);
						i_map.addPointers(i_key_2, i_value_2);

						a_result.assertTrue(0, "Key replacement should succeed", i_map.setKeyPointerByIndex(0, i_key_replacement));
						a_result.assertTrue(0, "Value replacement should succeed", i_map.setValuePointerByIndex(1, i_value_replacement));
						a_result.assertTrue(0, "Replacement key should be visible", i_map.getKeyPointerByIndex(0) == i_key_replacement);
						a_result.assertTrue(0, "Replacement value should be visible", i_map.getValuePointerByIndex(1) == i_value_replacement);
						a_result.assertTrue(0, "Null key replacement should fail", !i_map.setKeyPointerByIndex(0, nullptr));
						a_result.assertTrue(0, "Negative key replacement should fail", !i_map.setKeyPointerByIndex(-1, i_key_1));
						a_result.assertTrue(0, "Out of range value replacement should fail", !i_map.setValuePointerByIndex(3, i_value_1));
						a_result.assertTrue(0, "Null values should be supported", i_map.setValuePointerByIndex(1, nullptr));
						a_result.assertNull(0, "Null replacement value should be visible", i_map.getValuePointerByIndex(1));
					}

					delete i_key_1;
					delete i_key_2;
					delete i_key_replacement;
					delete i_value_1;
					delete i_value_2;
					delete i_value_replacement;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_4(pankey::Utility::Test::TestResult& a_result){
					int* i_keys[3] = {new int(1), new int(2), new int(3)};
					int* i_values[3] = {new int(10), new int(20), new int(30)};
					int* i_missing_key = new int(99);
					int* i_missing_value = new int(99);

					{
						PrimitiveIntegerMap i_map;
						i_map.expandLocalSize(3);
						for(int x = 0; x < 3; x++){
							i_map.addPointers(i_keys[x], i_values[x]);
						}

						a_result.assertTrue(0, "Middle removal should succeed", i_map.removePointersByIndex(1));
						a_result.assertEqual(0, "Middle removal should reduce length", i_map.length(), 2);
						a_result.assertTrue(0, "Removal should compact the final key", i_map.getKeyPointerByIndex(1) == i_keys[2]);
						a_result.assertTrue(0, "Removal should compact the final value", i_map.getValuePointerByIndex(1) == i_values[2]);
						a_result.assertTrue(0, "Missing key removal should fail", !i_map.removePointersByKeyPointer(i_missing_key));
						a_result.assertTrue(0, "Missing value removal should fail", !i_map.removePointersByValuePointer(i_missing_value));
						a_result.assertTrue(0, "Negative index removal should fail", !i_map.removePointersByIndex(-1));
						a_result.assertTrue(0, "Out of range removal should fail", !i_map.removePointersByIndex(2));
						a_result.assertTrue(0, "Key removal should find the remaining key", i_map.removePointersByKeyPointer(i_keys[0]));
						a_result.assertTrue(0, "Value removal should find the remaining value", i_map.removePointersByValuePointer(i_values[2]));
						a_result.assertTrue(0, "Map should be empty after all removals", i_map.isEmpty());
					}

					for(int x = 0; x < 3; x++){
						delete i_keys[x];
						delete i_values[x];
					}
					delete i_missing_key;
					delete i_missing_value;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_5(pankey::Utility::Test::TestResult& a_result){
					int* i_key_1 = new int(1);
					int* i_key_2 = new int(2);
					int* i_value_1 = new int(10);
					int* i_value_2 = new int(20);
					int* i_value_3 = new int(30);

					{
						PrimitiveIntegerMap i_map;
						i_map.expandLocalSize(2);
						i_map.addPointers(i_key_1, i_value_1);
						i_map.addPointers(i_key_2, i_value_2);
						i_map.clearValue();
						a_result.assertEqual(0, "clearValue should preserve length", i_map.length(), 2);
						a_result.assertNull(0, "clearValue should clear the first value", i_map.getValuePointerByIndex(0));
						a_result.assertNull(0, "clearValue should clear the second value", i_map.getValuePointerByIndex(1));
						a_result.assertTrue(0, "Keys should remain after clearValue", i_map.getKeyPointerByIndex(0) == i_key_1);
						i_map.setValuePointerByIndex(0, i_value_3);
						i_map.reset();
						a_result.assertTrue(0, "reset should empty the map", i_map.isEmpty());
						a_result.assertEqual(0, "reset should preserve capacity", i_map.getSize(), 2);
						i_map.addPointers(i_key_1, i_value_1);
						a_result.assertEqual(0, "length should be 1", i_map.length(), 1);
						i_map.clear();
						a_result.assertTrue(0, "clear should empty the map", i_map.isEmpty());
						a_result.assertEqual(0, "length should be 0", i_map.length(), 0);
						a_result.assertEqual(0, "clear should preserve capacity", i_map.getSize(), 2);
					}

					// delete i_key_1;
					delete i_key_2;
					// delete i_value_1;
					delete i_value_2;
					delete i_value_3;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_6(pankey::Utility::Test::TestResult& a_result){
					int* i_keys[3] = {new int(1), new int(2), new int(3)};
					int* i_values[3] = {new int(10), new int(20), new int(30)};

					{
						PrimitiveIntegerMap i_map;
						i_map.expandLocalSize(2);
						i_map.addPointers(i_keys[0], i_values[0]);
						i_map.addPointers(i_keys[1], i_values[1]);
						a_result.assertTrue(0, "Expansion should succeed", i_map.expandLocalSize(3));
						a_result.assertEqual(1, "Expansion should produce capacity five", i_map.getSize(), 5);
						a_result.assertTrue(2, "Insertion after expansion should succeed", i_map.addPointers(i_keys[2], i_values[2]));
						a_result.assertTrue(3, "Capacity shrink should succeed", i_map.shrinkLocalSize(2));
						a_result.assertEqual(4, "Capacity shrink should produce size three", i_map.getSize(), 3);
						a_result.assertTrue(5, "Logical shrink should succeed", i_map.shrinkLocal(1));
						a_result.assertEqual(6, "Logical shrink should remove one entry", i_map.length(), 2);
						a_result.assertTrue(7, "Zero expansion should fail", !i_map.expandLocalSize(0));
						a_result.assertTrue(8, "Zero capacity shrink should fail", !i_map.shrinkLocalSize(0));
						a_result.assertTrue(9, "Zero logical shrink should fail", !i_map.shrinkLocal(0));
					}

					for(int x = 0; x < 3; x++){
						delete i_keys[x];
						delete i_values[x];
					}
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing_7(pankey::Utility::Test::TestResult& a_result){
					int* i_key_1 = new int(1);
					int* i_key_2 = new int(2);
					int* i_key_3 = new int(3);
					int* i_value_1 = new int(10);
					int* i_value_2 = new int(20);
					int* i_value_3 = new int(30);

					{
						PrimitiveIntegerMap i_map;
						i_map.expandLocalSize(3);
						a_result.assertTrue(0, "putPointers should insert a new pair", i_map.putPointers(i_key_1, i_value_1));
						a_result.assertTrue(0, "putPointers should accept an existing pair", i_map.putPointers(i_key_1, i_value_1));
						a_result.assertEqual(0, "Duplicate put should not increase length", i_map.length(), 1);
						a_result.assertTrue(0, "setPointers should replace a value", i_map.setPointers(i_key_1, i_value_2));
						a_result.assertTrue(0, "Value lookup should return the replacement", i_map.getValuePointerByPointer(i_key_1) == i_value_2);
						a_result.assertTrue(0, "Key lookup should return the key", i_map.getKeyPointerByPointer(i_value_2) == i_key_1);
						a_result.assertTrue(0, "Fast insertion should succeed", i_map.addFastPointers(i_key_2, i_value_3));
						a_result.assertTrue(0, "Pair inequality should detect different maps", i_map != PrimitiveIntegerMap());
					}

					delete i_key_1;
					delete i_key_2;
					delete i_key_3;
					delete i_value_1;
					delete i_value_2;
					delete i_value_3;
				}

				void DataStructure_PrimitiveArrayRawPointerMap_Testing(pankey::Utility::Test::TestRunner& a_runner){
						a_runner.test("Primitive map empty state", DataStructure_PrimitiveArrayRawPointerMap_Testing_1);
						a_runner.test("Primitive map insertion and capacity", DataStructure_PrimitiveArrayRawPointerMap_Testing_2);
						a_runner.test("Primitive map replacement", DataStructure_PrimitiveArrayRawPointerMap_Testing_3);
						a_runner.test("Primitive map removal", DataStructure_PrimitiveArrayRawPointerMap_Testing_4);
						a_runner.test("Primitive map reset and clear", DataStructure_PrimitiveArrayRawPointerMap_Testing_5);
						a_runner.test("Primitive map resizing", DataStructure_PrimitiveArrayRawPointerMap_Testing_6);
						a_runner.test("Primitive map inherited operations", DataStructure_PrimitiveArrayRawPointerMap_Testing_7);
				}

				PANKEY_TEST_REGISTER(DataStructure_PrimitiveArrayRawPointerMap_Testing)

			}

		}

	}

}


