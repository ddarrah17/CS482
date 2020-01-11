#!/usr/bin/python

import argparse
import logging
import sys

import numpy as np

import gym
#import gym.scoreboard.scoring
from gym import wrappers, logger


################################################
# CS482: this is the function that changes the
# continuous values of the state of the cart-
# pole into a single integer state value, you'll
# have to adjust this for the mountain car task
################################################


def discretize_state( x, xdot):

    box = 0
    if x < -1.2 or -0.001 < xdot < 0.001:
        return -1

   #### -1.2 <-> 0.6 
    if x < -1.1:
        box = 0
    elif x < -1.0:
        box = 1
    elif x < -0.9:
        box = 2
    elif x < -0.8: 
        box = 3
    elif x < -0.7:
        box = 4
    elif x < -0.6: 
        box = 5
    elif x < -0.5:
        box = 6
    elif x < -0.4: 
        box = 7
    elif x < -0.3:
        box = 8
    elif x < -0.2:
        box = 9
    elif x < -0.1:
        box = 10
    elif x < 0: 
        box = 11
    elif x < 0.1: 
        box = 12
    elif x < 0.2:
        box = 13
    elif x < 0.3:
        box = 14
    elif x < 0.4:
        box = 15
    elif x < 0.5:
        box = 16
    elif x < 0.6:
        box = 17
    else:
        box = 18

    #### -0.6 <-> 0.6
    box *= 14
    if xdot < -0.6:
        box += 0
    elif xdot < -0.5:
        box += 1
    elif xdot < -0.4:
        box += 2
    elif xdot < -0.3:
        box += 3
    elif xdot < -0.2:
        box += 4
    elif xdot < -0.1:
        box += 5
    elif xdot < 0:
        box += 6
    elif xdot < 0.1: 
        box += 7
    elif xdot < 0.2: 
        box += 8
    elif xdot < 0.3: 
        box += 9
    elif xdot < 0.4: 
        box += 10
    elif xdot < 0.5: 
        box += 11
    elif xdot < 0.6:
        box += 12
    else:
        box += 13


    return box

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=None)

    ############################################
    # CS482: This is the line you'll have to
    # change to switch to the mountain car task
    ############################################
    parser.add_argument('env_id', nargs='?', default='MountainCar-v0', help='Select the environment to run')
    args = parser.parse_args()

    logger = logging.getLogger()
    formatter = logging.Formatter('[%(asctime)s] %(message)s')
    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    # You can set the level to logging.DEBUG or logging.WARN if you
    # want to change the amount of output.
    logger.setLevel(logging.INFO)

    env = gym.make(args.env_id)
    outdir = '/tmp/' + 'qagent' + '-results'
    env = wrappers.Monitor(env, outdir, write_upon_reset=True, force=True)

    env.seed(0)

    ############################################
    # CS482: This initial Q-table size should 
    # change to fit the number of actions (columns)
    # and the number of observations (rows)
    ############################################


    Q = np.zeros([300, env.action_space.n])

    ############################################
    # CS482: Here are some of the RL parameters
    # you can adjust to change the learning rate
    # (alpha) and the discount factor (gamma)
    ############################################

    alpha = 0.95
    gamma = 0.35
    Succcount = 0
    failcount = 0

    n_episodes = 50001
    for episode in range(n_episodes):
        tick = 0
        reward = 0
        done = False
        state = env.reset()
        s = discretize_state(state[0], state[1])
        while done != True:
            tick += 1
            action = 0
            ri = -999
            for q in range(env.action_space.n):
                if Q[s][q] > ri:
                    action = q
                    ri = Q[s][q]
            state, reward, done, info = env.step(action)
            sprime = discretize_state(state[0], state[1])
            predicted_value = np.max(Q[sprime])
            if sprime < 0:
                predicted_value = 0
                reward = -5
                
            Q[s,action] += alpha * (reward + gamma * predicted_value - Q[s,action])


            s = sprime

        if episode % 1000 == 0:
            alpha *= .996

        ############################################
        # CS482: When switching to the mountain car
        # task, you will have to change this to
        # reflect the success/failure of the mountain
        # car task
        ############################################
       
        if 0.5 < state[0]:
            Succcount =  Succcount + 1
            print "success", "Count: ",  Succcount 
        else:
            failcount = failcount + 1
            print "fail", "Count: ", failcount, " STATE: ", state[0]
