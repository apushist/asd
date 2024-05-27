#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

#include "abstract_database.h"


class MyDatabase : public AbstractDatabase {
private:
	//ключ - пара ownerId, id
	std::unordered_map<std::pair<int,int>,Post> posts;
	std::unordered_map<int, User> users;

public:

	const Post& get_post(int ownerId, int postId) override {
		std::pair<int, int> key = std::make_pair(ownerId, postId);
		if (posts.find(key) != posts.end()) 
			return posts[key];
		throw DatabaseException("Post not found");
	}

	const User& get_user(int id) override {
		if (users.find(id) != users.end())
			return users[id];
		throw DatabaseException("User not found");
	}

	void insert_post(const Post& post) override {
		posts[std::make_pair(post.OwnerId,post.Id)] = post;
	}

	void insert_user(const User& user) override {
		users[user.Id] = user;
	}

	void delete_post(int ownerId, int postId) override {
		posts.erase(std::make_pair(ownerId, postId));
	}

	void like_post(int ownerId, int postId) override {
		std::pair<int, int> key = std::make_pair(ownerId, postId);
		if (posts.find(key) != posts.end()) {
			posts[key].Likes++;
		}
	}

	void unlike_post(int ownerId, int postId) override {
		std::pair<int, int> key = std::make_pair(ownerId, postId);
		if (posts.find(key) != posts.end()) {
			if(posts[key].Likes > 0)
				posts[key].Likes--;
		}
	}

	void repost_post(int ownerId, int postId) override {
		std::pair<int, int> key = std::make_pair(ownerId, postId);
		if (posts.find(key) != posts.end()) {
			posts[key].Reposts++;
		}
	}

	std::vector<Post> top_k_post_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<Post> result; 
		std::vector<std::pair<Post, int>> postsByLikes; // пост - количество лайков
		for (const auto& pair : posts) {
			const Post& post = pair.second;
			if (post.OwnerId == ownerId && post.Date >= dateBegin && post.Date <= dateEnd) {
				postsByLikes.push_back(std::make_pair(post, post.Likes));
			}
		}

		std::sort(postsByLikes.begin(), postsByLikes.end(), 
			[](const std::pair<Post, int>& a, const std::pair<Post, int>& b) {
			return a.second > b.second;
			});

		for (int i = 0; i < k && i < postsByLikes.size(); ++i) {
			result.push_back(postsByLikes[i].first);
		}

		return result;
	}

	std::vector<Post> top_k_post_by_reposts(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<Post> result; 
		std::vector<std::pair<Post, int>> postsByReposts; // пост - количество репостов
		for (const auto& pair : posts) {
			const Post& post = pair.second;
			if (post.OwnerId == ownerId && post.Date >= dateBegin && post.Date <= dateEnd) {
				postsByReposts.push_back(std::make_pair(post, post.Reposts));
			}
		}

		std::sort(postsByReposts.begin(), postsByReposts.end(),
			[](const std::pair<Post, int>& a, const std::pair<Post, int>& b) {
				return a.second > b.second;
			});

		for (int i = 0; i < k && i < postsByReposts.size(); ++i) {
			result.push_back(postsByReposts[i].first);
		}

		return result;
	}

	std::vector<UserWithLikes> top_k_authors_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {

		std::vector<UserWithLikes> result;
		
		std::unordered_map<int, int> usersLikes;//authorID - likes
		for (const auto& pair : posts) {
			const Post& post = pair.second;
			if (post.OwnerId == ownerId && post.Date >= dateBegin && post.Date <= dateEnd) {
				usersLikes[post.FromId] += post.Likes;
			}
		}

		std::vector<std::pair<int, int>> usersVector(usersLikes.begin(), usersLikes.end());

		std::sort(usersVector.begin(), usersVector.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second > b.second;
			});

		for (int i = 0; i < k && i < usersVector.size(); i++) {
			std::pair<int,int> value = usersVector[i];
			if(users.find(value.first) == users.end())
				throw DatabaseException("User not found");
			UserWithLikes userWithLikes = { users[value.first], value.second };
			result.push_back(userWithLikes);
		}

		return result;
	}

	std::vector<UserWithReposts> top_k_authors_by_reports(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<UserWithReposts> result;

		std::unordered_map<int, int> usersReposts;//authorID - Reposts
		for (const auto& pair : posts) {
			const Post& post = pair.second;
			if (post.OwnerId == ownerId && post.Date >= dateBegin && post.Date <= dateEnd) {
				usersReposts[post.FromId] += post.Reposts;
			}
		}

		std::vector<std::pair<int, int>> usersVector(usersReposts.begin(), usersReposts.end());

		std::sort(usersVector.begin(), usersVector.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second > b.second;
			});

		for (int i = 0; i < k && i < usersVector.size(); i++) {
			std::pair<int, int> value = usersVector[i];
			if (users.find(value.first) == users.end())
				throw DatabaseException("User not found");
			UserWithReposts userWithReposts = { users[value.first], value.second };
			result.push_back(userWithReposts);
		}

		return result;
	}


};
