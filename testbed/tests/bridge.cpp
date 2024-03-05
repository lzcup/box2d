// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test.h"

class Bridge : public Test
{
public:

	enum
	{
		e_count = 200
	};

	Bridge()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);
		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.125f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;

			b2RevoluteJointDef jd;

			b2Body* prevBody = ground;
			for (int32 i = 0; i < e_count; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(-34.5f + 1.0f * i, 20.0f);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&fd);

				b2Vec2 anchor(-35.0f + 1.0f * i, 20.0f);
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);

				if (i == (e_count >> 1))
				{
					m_middle = body;
				}
				prevBody = body;
			}

			b2Vec2 anchor(-35.0f + 1.0f * e_count, 20.0f);
			jd.Initialize(prevBody, ground, anchor);
			m_world->CreateJoint(&jd);
		}

		for (int32 i = 0; i < 2; ++i)
		{
			b2Vec2 vertices[3];
			vertices[0].Set(-0.5f, 0.0f);
			vertices[1].Set(0.5f, 0.0f);
			vertices[2].Set(0.0f, 1.5f);

			b2PolygonShape shape;
			shape.Set(vertices, 3);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-8.0f + 8.0f * i, 22.0f);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}

		for (int32 i = 0; i < 3; ++i)
		{
			b2CircleShape shape;
			shape.m_radius = 0.5f;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-6.0f + 6.0f * i, 25.0f);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}
	}

	static Test* Create()
	{
		return new Bridge;
	}

	b2Body* m_middle;
};

static int testIndex = RegisterTest("Joints", "Bridge", Bridge::Create);

class BallAndChain : public Test
{
public:

	enum
	{
		e_count = 30
	};

	BallAndChain()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);
		}

		{
			float hx = 0.5f;
			b2PolygonShape box;
			box.SetAsBox(hx, 0.125f);

			b2FixtureDef fd;
			fd.shape = &box;
			fd.density = 20.0f;

			b2RevoluteJointDef jd;

			b2Body* prevBody = ground;
			for (int32 i = 0; i < e_count; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set((1.0f + 2.0f * i) * hx, e_count * hx);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&fd);

				b2Vec2 anchor((2.0f * i) * hx, e_count * hx);
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);
				prevBody = body;
			}

			b2CircleShape circle;
			circle.m_radius = 4.0f;
			fd.shape = &circle;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set((1.0f + 2.0f * e_count) * hx + circle.m_radius - hx, e_count * hx);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);

			b2Vec2 anchor((2.0f * e_count) * hx, e_count * hx);
			jd.Initialize(prevBody, body, anchor);
			m_world->CreateJoint(&jd);
		}
	}

	static Test* Create()
	{
		return new BallAndChain;
	}
};

static int testBallAndChainIndex = RegisterTest("Joints", "BallAndChain", BallAndChain::Create);
