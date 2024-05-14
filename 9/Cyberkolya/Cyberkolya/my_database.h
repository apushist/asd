#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "abstract_database.h"


class LegacyDatabase : public AbstractDatabase {
private:
	std::vector<Post> posts;
	std::vector<User> users;

	auto get_post_it(int ownerId, int postId) {
		throw std::exception("Not implemented");
	}

	auto get_user_it(int id) {
		throw std::exception("Not implemented");
	}

public:
	void dump_tsv_posts(std::wostream& stream) {
		throw std::exception("Not implemented");
	}

	void dump_tsv_users(std::wostream& stream) {
		throw std::exception("Not implemented");
	}

	const Post& get_post(int ownerId, int postId) override {
		throw std::exception("Not implemented");
		throw DatabaseException("Post not found");
	}

	const User& get_user(int id) override {
		throw std::exception("Not implemented");
		throw DatabaseException("User not found");
	}

	void insert_post(const Post& post) override {
		throw std::exception("Not implemented");
	}

	void insert_user(const User& user) override {
		throw std::exception("Not implemented");
	}

	void delete_post(int ownerId, int postId) override {
		throw std::exception("Not implemented");
	}

	void like_post(int ownerId, int postId) override {
		throw std::exception("Not implemented");
	}

	void unlike_post(int ownerId, int postId) override {
		throw std::exception("Not implemented");
	}

	void repost_post(int ownerId, int postId) override {
		throw std::exception("Not implemented");
	}

	std::vector<Post> top_k_post_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw std::exception("Not implemented");
	}

	std::vector<Post> top_k_post_by_reposts(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw std::exception("Not implemented");
	}

	std::vector<UserWithLikes> top_k_authors_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw std::exception("Not implemented");
	}

	std::vector<UserWithReposts> top_k_authors_by_reports(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw std::exception("Not implemented");
	}
};
