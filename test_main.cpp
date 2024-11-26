#include "Database.h"
#include <gtest/gtest.h>

TEST(DatabaseTest, CreateTable) {
    Database db;
    db.execute("create table users id name age");
    ASSERT_TRUE(db.tables.find("users") != db.tables.end());
}

TEST(DatabaseTest, InsertRecord) {
    Database db;
    db.execute("create table users id name age");
    db.execute("insert id 1 name Alice age 30 to users");
    ASSERT_EQ(db.tables["users"].records.size(), 1);
}

TEST(DatabaseTest, SelectRecords) {
    Database db;
    db.execute("create table users id name age");
    db.execute("insert id 1 name Alice age 30 to users");
    db.execute("insert id 2 name Bob age 25 to users");
    db.execute("select * from users");
    ASSERT_EQ(db.tables["users"].records.size(), 2);
}

TEST(DatabaseTest, UpdateRecord) {
    Database db;
    db.execute("create table users id name age");
    db.execute("insert id 1 name Alice age 30 to users");
    db.execute("update users set name Bob where id 1");
    ASSERT_EQ(db.tables["users"].records[0].fields["name"], "Bob");
}

TEST(DatabaseTest, DeleteRecord) {
    Database db;
    db.execute("create table users id name age");
    db.execute("insert id 1 name Alice age 30 to users");
    db.execute("insert id 2 name Bob age 25 to users");
    db.execute("delete users where id 1");
    ASSERT_EQ(db.tables["users"].records.size(), 1);
    ASSERT_EQ(db.tables["users"].records[0].fields["id"], "2");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
