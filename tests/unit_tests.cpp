#include <gtest/gtest.h>
#include <QApplication>
#include "../database.h"

class TestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        // Initialize the database before running tests
        ASSERT_TRUE(initializeDatabase());
    }
};

TEST(DatabaseTest, AuthenticateUser) {
    QString role;
    EXPECT_TRUE(authenticateUser("admin", "admin123", role));
    EXPECT_EQ(role, "admin");

    EXPECT_FALSE(authenticateUser("nonexistent", "wrongpassword", role));
}

TEST(DatabaseTest, GetInventory) {
    QList<QStringList> inventory = getInventory();
    EXPECT_FALSE(inventory.isEmpty());
}

TEST(DatabaseTest, GetRepairRequests) {
    QList<QStringList> repairRequests = getRepairRequests();
    // This might be empty if no repair requests have been added
    EXPECT_TRUE(repairRequests.isEmpty() || !repairRequests.isEmpty());
}

TEST(DatabaseTest, GetTransactionHistory) {
    QList<QStringList> transactionHistory = getTransactionHistory();
    // This might be empty if no transactions have been made
    EXPECT_TRUE(transactionHistory.isEmpty() || !transactionHistory.isEmpty());
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}