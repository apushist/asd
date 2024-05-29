#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <queue>
#include <functional>

#include "abstract_database.h"


class MyDatabase : public AbstractDatabase {
private:
	std::unordered_map<int, std::unordered_map<int, Post>> posts;
	std::unordered_map<int, User> users;

public:

	const Post& get_post(int ownerId, int postId) override {
		if (posts.find(ownerId) != posts.end())
			if (posts[ownerId].find(postId) != posts[ownerId].end())
				return posts[ownerId][postId];
		throw DatabaseException("Post not found");
	}

	const User& get_user(int id) override {
		if (users.find(id) != users.end())
			return users[id];
		throw DatabaseException("User not found");
	}

	void insert_post(const Post& post) override {
		posts[post.OwnerId][post.Id] = post;
	}

	void insert_user(const User& user) override {
		users[user.Id] = user;
	}

	void delete_post(int ownerId, int postId) override {
		if (posts.find(ownerId) != posts.end())
			posts[ownerId].erase(postId);
	}

	void like_post(int ownerId, int postId) override {
		if (posts.find(ownerId) != posts.end())
			if (posts[ownerId].find(postId) != posts[ownerId].end())
				posts[ownerId][postId].Likes++;
	}

	void unlike_post(int ownerId, int postId) override {
		if (posts.find(ownerId) != posts.end())
			if (posts[ownerId].find(postId) != posts[ownerId].end())
				posts[ownerId][postId].Likes--;

	}

	void repost_post(int ownerId, int postId) override {
		if (posts.find(ownerId) != posts.end())
			if (posts[ownerId].find(postId) != posts[ownerId].end())
				posts[ownerId][postId].Reposts++;
	}
	struct PostComparator {
			bool operator()(const std::pair<int, Post>& a, const std::pair<int, Post>& b) {
				return a.first < b.first;
			}
		};

	std::vector<Post> top_k_post_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<Post> result;
		std::priority_queue<std::pair<int, Post>, std::vector<std::pair<int, Post>>, PostComparator> pq;

		if (posts.find(ownerId) != posts.end()) {
			for (const auto& post : posts[ownerId]) {
				if (post.second.Date >= dateBegin && post.second.Date < dateEnd) {
					pq.push({ post.second.Likes, post.second });
					
				}
			}
		}

		while (!pq.empty() && result.size() < k) {
			result.push_back(pq.top().second);
			pq.pop();
		}

		return result;
	}

	std::vector<Post> top_k_post_by_reposts(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<Post> result;
		std::priority_queue<std::pair<int, Post>, std::vector<std::pair<int, Post>>, PostComparator> pq;

		if (posts.find(ownerId) != posts.end()) {
			for (const auto& post : posts[ownerId]) {
				if (post.second.Date >= dateBegin && post.second.Date < dateEnd) {
					pq.push({ post.second.Reposts, post.second });

				}
			}
		}

		while (!pq.empty() && result.size() < k) {
			result.push_back(pq.top().second);
			pq.pop();
		}


		return result;
	}

	
	struct UserComparator {
		bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second < b.second;
		}
	};
	
	std::vector<UserWithLikes> top_k_authors_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
	
		std::vector<UserWithLikes> result;
		
		std::unordered_map<int, int> usersLikes;//authorID - likes
		if (posts.find(ownerId) != posts.end()) {
			for (const auto& pair : posts[ownerId]) {
				const Post& post = pair.second;
				if (post.Date >= dateBegin && post.Date < dateEnd) {
					usersLikes[post.FromId] += post.Likes;
				}
			}
		}
		
		std::priority_queue<std::pair<int, int>, 
			std::vector<std::pair<int, int>>, 
			UserComparator
		> usersQueue(usersLikes.begin(), usersLikes.end());
	
		while (!usersQueue.empty() && result.size() < k) {
			std::pair<int, int> topUser = usersQueue.top();
			usersQueue.pop();
			if(users.find(topUser.first) == users.end())
				throw DatabaseException("User not found");
			UserWithLikes userWithLikes = { users[topUser.first], topUser.second };
			result.push_back(userWithLikes);
		}
	
		return result;
	}
	
	std::vector<UserWithReposts> top_k_authors_by_reports(int k, int ownerId, int dateBegin, int dateEnd) override {
		std::vector<UserWithReposts> result;
	
		std::unordered_map<int, int> usersReposts;//authorID - Reposts
		if (posts.find(ownerId) != posts.end()) {
			for (const auto& pair : posts[ownerId]) {
				const Post& post = pair.second;
				if (post.Date >= dateBegin && post.Date < dateEnd) {
					usersReposts[post.FromId] += post.Reposts;
				}
			}
		}
	
		std::priority_queue<std::pair<int, int>,
			std::vector<std::pair<int, int>>,
			UserComparator
		> usersQueue(usersReposts.begin(), usersReposts.end());

		while (!usersQueue.empty() && result.size() < k) {
			std::pair<int, int> topUser = usersQueue.top();
			usersQueue.pop();
			if (users.find(topUser.first) == users.end())
				throw DatabaseException("User not found");
			UserWithReposts userWithReposts = { users[topUser.first], topUser.second };
			result.push_back(userWithReposts);
		}
		return result;
	}


};
